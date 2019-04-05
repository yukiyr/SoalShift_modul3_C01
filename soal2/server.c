#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <termios.h>

#define PORT 2323

int *value; 

void* cetak(){
    while(1){
        printf("Stok barang : %d\n", *value);
        sleep(5);
    }
}

void* server(){
    int server_fd, valread, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0){
        while((valread = read( new_socket , buffer, 1024)) > 0){
            if(strcmp(buffer, "tambah") == 0){
                *value += 1;
            }
            memset(buffer, 0, sizeof(buffer));
        }
    }
}

int main(int argc, char const *argv[]) {
    pthread_t thread, ctk;
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    pthread_create(&thread, NULL, server, NULL);
    pthread_create(&ctk, NULL, cetak, NULL);
    pthread_join(thread, NULL);
    pthread_join(ctk, NULL);
    

    shmdt(value);
    shmctl(shmid , IPC_RMID,NULL);
    return 0;
}
