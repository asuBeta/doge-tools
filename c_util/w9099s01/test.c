#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "w9099s01.h"

// gcc test.c -L. -lw9099s01 -o test

int main(){
    
    FILE *file = NULL;
    char buff[1024];
    
    memset(buff, 0x00, sizeof(buff));
    
    file = fopen("/Users/qtao/mygit/c_util/w9099s01/test.csv", "r");
    
    if(file == NULL) exit(-1);
    
    while (fgets(buff, 1024, file) != NULL){
        printf("%s", buff);
    }
    
    if (file != NULL) {
        fclose(file);
        printf("file colsed!\n");
    }
    
    return 0;
}