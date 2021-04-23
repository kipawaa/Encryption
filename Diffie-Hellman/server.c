#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h> // needed for memset
#include<sys/socket.h> // make sockets work
#include<netinet/in.h> // make internets work
#include<arpa/inet.h> // apparently necessary for macOS??

int main() {
        int error;


        // create a socket on this computer
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (serverSocket == -1) {
                perror("socket creation error");
                exit(1);
        }

        struct sockaddr_in serverSocketAddress;
        serverSocketAddress.sin_family = AF_INET;
        serverSocketAddress.sin_port = htons(52958); // htons makes sure every machine interprets this the same way
        serverSocketAddress.sin_addr.s_addr = INADDR_ANY;
        memset(&(serverSocketAddress.sin_zero), 0, 8); 
        // supposedly sockaddr_in.sin_zero is extra space and may contain information from your computer
        // so it's a good idea to wipe that memory before sending it anywhere

        // bind the socket to a port
        error = bind(serverSocket, (struct sockaddr*) &serverSocketAddress, sizeof(struct sockaddr_in));
        
        if (error) {
                perror("binding error");
                exit(2);
        }

        // listen for clients, up to 5 in backlog
        error = listen(serverSocket, 5);
        
        if (error < 0) {
                perror("listen error");
                exit(3);
        }

        // create a struct to store the address of the client
        struct sockaddr_in clientSocketAddress;
        clientSocketAddress.sin_family = AF_INET;


        // accept a connection
        unsigned int clientAddressLength = sizeof(struct sockaddr_in);
        int clientSocket = accept(serverSocket, (struct sockaddr*) &clientSocketAddress, &clientAddressLength);

        if (clientSocket == -1) {
                perror("accept error");
                exit(4);
        }

        int data = 19;// TODO get diffie hellman number here

        // now we're connected! we need to share data
        // let's send the client our data first
        error = write(clientSocket, &data, sizeof(int));

        // get the client's data
        int clientData;

        read(clientSocket, &clientData, sizeof(int));

        // show the user the client data
        printf("client data: %d\n", clientData);

        // close the server
        close(serverSocket);
}
