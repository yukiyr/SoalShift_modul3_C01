#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include <pthread.h>

#define PORT 2323

int *value;

void* client(){
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
    }

    while(1){
        char arr[10];
        scanf("%s", arr);
        send(sock , arr, strlen(arr) , 0 );
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        memset(buffer, 0, sizeof(buffer));
    }
}
  
int main(int argc, char const *argv[]) {
    pthread_t thread;

    pthread_create(&thread, NULL, client, NULL);
    pthread_join(thread, NULL);

    return 0;
}
