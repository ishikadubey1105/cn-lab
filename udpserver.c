// UDP Echo Server  |  Compile: gcc udpserver.c -o udpserver  |  Run: ./udpserver (FIRST)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 10055
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE];
    socklen_t addrlen = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { perror("bind"); exit(1); }
    printf("UDP Echo Server listening on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int bytes = recvfrom(sockfd, buffer, BUF_SIZE - 1, 0,
                             (struct sockaddr *)&client_addr, &addrlen);
        if (bytes <= 0) continue;

        printf("Received: %s", buffer);
        sendto(sockfd, buffer, bytes, 0, (struct sockaddr *)&client_addr, addrlen);
    }
    close(sockfd);
    return 0;
}
