#include<stdio.h>
#include<stdlib.h>
#include<time.h> // for RNG seeding
#include<unistd.h>
#include<string.h> // needed for memset
#include<sys/socket.h> // make sockets work
#include<netinet/in.h> // make internets work
#include<arpa/inet.h> // apparently necessary for macOS??
#include<netdb.h>

#include"DHKE-server.h"

int main() {
        // seed RNG
        srand(time(0));
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

        // listen for clients
        error = listen(serverSocket, 1);
        if (error < 0) {
                perror("listen error");
                exit(1);
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

        // now we're connected! we need to share data

        // this is the server, so we'll handle the generation of the base a modulus
        int min;
        int max;
        printf("enter the space separated range in which you would like your prime modulus (ex. 100 5000): ");
        scanf("%d %d", &min, &max);

        // get the modulus
        int mod = get_prime(min, max);

        // get a primitive root
        int base = get_primitive_root(mod);

        // send the modulus to the client
        error = write(clientSocket, &mod, sizeof(int));
        if (error != sizeof(int)) {
                perror("write error");
                exit(1);
        }
        
        // send the base to the client
        error = write(clientSocket, &base, sizeof(int));
        if (error != sizeof(int)) {
                perror("write error");
                exit(1);
        }

        // now that they've got the modulus and base, let's send them our secret number
        int serverPrivateKey = rand() % mod;
        int serverPublicKey = mod_exp(base, serverPrivateKey, mod);

        error = write(clientSocket, &serverPublicKey, sizeof(int));
        if (error != sizeof(int)) {
                perror("write error");
                exit(5);
        }

        // get the client's data
        int clientPublicKey;

        error = read(clientSocket, &clientPublicKey, sizeof(int));
        if (error != sizeof(int)) {
                perror("read error");
                exit(1);
        }

        int secretKey = mod_exp(clientPublicKey, serverPrivateKey, mod);

        // show the user the client data
        printf("secret key: %d\n", secretKey);

        // close the server
        close(serverSocket);
}
