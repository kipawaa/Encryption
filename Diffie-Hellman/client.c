#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
        int error;

        // create a socket for me
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        if (clientSocket == -1) {
                perror("socket error");
                exit(1);
        }

        // create a struct to store server address
        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(52958);
        memset((&serverAddress.sin_zero), 0, 8);

        // connect to the server
        error = connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr_in));

        if (error) {
                perror("connection error");
                exit(2);
        }

        // once connected, we read first
        int serverData;

        read(clientSocket, &serverData, sizeof(int));

        printf("friend's number is: %d\n", serverData);

        // get our number
        int clientData = 12;//TODO add diffie hellman stuff here

        // once we're done reading, write our number back
        write(clientSocket, &clientData, sizeof(int));

        // close socket when we're done
        close(clientSocket);
}
