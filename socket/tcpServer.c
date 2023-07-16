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
    int serverClient;
    socklen_t addr_size;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    char buffer[BUFFER_SIZE];
    char bufferUser[BUFFER_SIZE];

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bindCheck = bind(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(clientSocket, 5);
    addr_size = sizeof(clientAddr);
    serverClient = accept(clientSocket, (struct sockaddr*)&clientAddr, &addr_size);

    strcpy(buffer, "Hello client I am going to send you information");
    send(serverClient, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));

    while (1) {
        fgets(bufferUser, BUFFER_SIZE, stdin);
        bufferUser[strcspn(bufferUser, "\n")] = '\0';  // Remove trailing newline character
        strcpy(buffer, bufferUser);
        send(serverClient, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
    }
    return 0;
}
