#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include"DHKE-client.h"

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

        // now we're connected!
        // first we'll be sent the modulus:
        int mod;
        read(clientSocket, &mod, sizeof(int));

        // then we'll be sent the base:
        int base;
        read(clientSocket, &base, sizeof(int));

        // then we'll be sent the server's public key
        int serverPublicKey;
        read(clientSocket, &serverPublicKey, sizeof(int));

        // get our number
        int clientPrivateKey = rand() % mod;
        int clientPublicKey = mod_exp(base, clientPrivateKey, mod);

        // now we send the server our public key
        write(clientSocket, &clientPublicKey, sizeof(int));

        // and compute the shared secret key!
        int secretKey = mod_exp(serverPublicKey, clientPrivateKey, mod);

        printf("the shared secret key is: %d\n", secretKey);

        // close socket when we're done
        close(clientSocket);
}
