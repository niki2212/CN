#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sockfd, valread;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024] = {0};
    FILE *fp;

    // Create socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Fill server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    unsigned int len, n;
    len = sizeof(cliaddr);

    // Receive filename from client
    n = recvfrom(sockfd, buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';

    printf("Received file: %s\n", buffer);

    // Open file for writing
    fp = fopen(buffer, "w");
    if (fp == NULL) {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    // Receive file contents from client and write to file
    while ((n = recvfrom(sockfd, buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len)) > 0) {
        fwrite(buffer, 1, n, fp);
    }

    printf("File received successfully!\n");

    fclose(fp);
    close(sockfd);

    return 0;
}