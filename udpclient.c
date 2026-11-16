// UDP Echo Client  |  Compile: gcc udpclient.c -o udpclient  |  Run: ./udpclient
// NOTE: PORT is 10055 = same as server (your old client had 10012 -> mismatch, fixed)
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
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Enter message: ");
        if (fgets(buffer, BUF_SIZE, stdin) == NULL) break;   // Ctrl+D to quit
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr));

        memset(buffer, 0, BUF_SIZE);
        int bytes = recvfrom(sockfd, buffer, BUF_SIZE - 1, 0, NULL, NULL);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        printf("Echo from server: %s", buffer);
    }
    close(sockfd);
    return 0;
}
