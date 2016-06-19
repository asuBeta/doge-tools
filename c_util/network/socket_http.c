#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> // socket
#include <arpa/inet.h> // htons
//#include <netinet/in.h>
#include <netdb.h>

int socket_server();
int socket_client(const char *deststr);
int socket_server_udp();
int socket_client_udp();

int main()
{
    int ret = 0;
    
    ret = socket_server();
    //ret = socket_client("127.0.0.1");
    
    return ret;
}


// tcp socket server: create->bind->listen->accept->recieve/send->close
int socket_server()
{
    int sock0;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    int len;
    int sock;
    int yes = 1;
    int ret = 0;
    char buf[2048];
    char buf2[2048];
    
    memset(buf, 0x00, sizeof(buf));
    memset(buf2, 0x00, sizeof(buf2));
    
    // use TCP
    sock0 =  socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock0 < 0) {
        perror("socket");
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    // allow local address reuse
    setsockopt(sock0, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    
    if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("bind");
        return 1;
    }
    
    if (listen(sock0, 5) != 0) {
        perror("listen");
        return 1;
    }
    
    snprintf(buf, sizeof(buf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "\r\n"
             "<h1 style='color:red' >Hello, World!</h1>\r\n");
    
    while (1) {
        len = sizeof(client);
        sock =  accept(sock0, (struct sockaddr *)&client, (socklen_t *)&len);
        
        if (sock < 0) {
            perror("accept");
            ret = 1;
            break;
        }
        
        printf("accepted connection from %s, port=%d\n",
               inet_ntoa(client.sin_addr),
               client.sin_port);
        
        recv(sock, buf2, sizeof(buf2), 0);
        printf("%s", buf2);
        
        if (send(sock, buf, strlen(buf), 0) < 1) {
            perror("send");
            ret = 1;
            break;
        }
        
        close(sock);
    }
    
    close(sock0);
    
    return ret;
    
}

// tcp socket client: create->connect->recieve/send->close
int socket_client(const char *deststr)
{
    struct sockaddr_in server;
    int sock;
    char buf[2048];
    unsigned int **addrptr;
    
    // use TCP
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    
    server.sin_addr.s_addr = inet_addr(deststr);
    if (server.sin_addr.s_addr == 0xffffffff) {
        struct hostent *host;
        
        host = gethostbyname(deststr);
        if (host == NULL) {
            if (h_errno == HOST_NOT_FOUND) {
                // h_errno is an extern var
                printf("host not found : %s\n", deststr);
            } else {
                printf("%s : %s\n", hstrerror(h_errno), deststr);
            }
            return 1;
        }
        
        addrptr = (unsigned int **)host->h_addr_list;
        
        while (*addrptr != NULL) {
            server.sin_addr.s_addr = *(*addrptr);
            
            if (connect(sock,
                        (struct sockaddr *)&server,
                        sizeof(server)) == 0) {
                break;
            }
            
            addrptr++;
            // retry
        }
        
        /* connect failed */
        if (*addrptr == NULL) {
            perror("connect");
            return 1;
        }
    } else {
        if (connect(sock,
                    (struct sockaddr *)&server, sizeof(server)) != 0) {
            perror("connect");
            return 1;
        }
    }
    
    // generate request
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "GET / HTTP/1.0\r\n\r\n");
    
    // HTTP send
    ssize_t n = write(sock, buf, strlen(buf));
    if (n < 0) {
        perror("write");
        return 1;
    }
    
    // http receive
    while (n > 0) {
        memset(buf, 0, sizeof(buf));
        n = read(sock, buf, sizeof(buf));
        if (n < 0) {
            perror("read");
            return 1;
        }
        
        // print output(1:standard output)
        write(1, buf, strlen(buf));
    }
    
    close(sock);
    
    return 0;
}
