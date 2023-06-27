#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sockfd, valread;
    struct sockaddr_in servaddr;
    char file[1024] = {0};
    char buffer[1024] = {0};
    FILE *fp;

    // Create socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        perror("invalid address/ address not supported");
        exit(EXIT_FAILURE);
    }

    // Get file from user
    printf("Enter the file to send: ");
    scanf("%s", file);

    // Send file to server
    sendto(sockfd, file, strlen(file), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Open file for reading
    fp = fopen(file, "r");
    if (fp == NULL) {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    // Send file contents to server
    while (fgets(buffer, 1024, fp) != NULL) {
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        memset(buffer, 0, sizeof(buffer));
    }

    fclose(fp);
    close(sockfd);

    return 0;
}