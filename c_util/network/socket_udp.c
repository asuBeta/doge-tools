#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> // socket
#include <arpa/inet.h> // htons
//#include <netinet/in.h>
#include <netdb.h>

int socket_server_udp();
int socket_client_udp();

int main()
{
	int ret = 0;
	//ret = socket_server_udp();
	ret = socket_client_udp();
	
	return ret;
}

// udp socket server: create->send->close
int socket_server_udp()
{
	int sock = 0;
	int yes = 1;
	char buf[2048];
	struct sockaddr_in addr;
	
	memset(buf, 0x00, sizeof(buf));
	
	// use UDP
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (sock < 0) {
		perror("sock");
		return 1;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12346);
	addr.sin_addr.s_addr = inet_addr("255.255.255.255"); // for broadcast
	
	// use broadcast
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));
	
	strcpy(buf, "HELLO!!");
	
	if (sendto(sock, buf, strlen(buf), 0,
			   (struct sockaddr*)&addr, sizeof(addr)) < 0 ) {
		perror("send");
		return 1;
	}
	
	close(sock);

	return 0;
}


// udp socket client: create->bind->recieve->close
int socket_client_udp()
{
	int ret = 0;
	int sock;
	char buf[2048];
	ssize_t count = 1;
	struct sockaddr_in addr;
	
	memset(buf, 0x00, sizeof(buf));
	
	// use UDP
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (sock < 0) {
		perror("sock");
		return 1;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12346); // host on short
	addr.sin_addr.s_addr = INADDR_ANY;
	
	ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	
	if (ret < 0) {
		perror("bind");
		return 1;
	}
	
	while (count) {
		count = recv(sock, buf, sizeof(buf), 0);
		printf("%s\n", buf);
	}
	
	close(sock);
	
	return 0;
}
