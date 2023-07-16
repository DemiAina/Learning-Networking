#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 49155
#define BUFFER_SIZE 1024

int main(void) {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int succ = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    if (succ == 0) {
        printf("Connection to the web service successful\n");

        while (1) {
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);

            if (bytesReceived <= 0) {
                printf("Connection closed by the server\n");
                break;
            }

            printf("Data received: %s\n", buffer);
        }
    } else {
        printf("Connection failed\n");
    }

    return 0;
}

