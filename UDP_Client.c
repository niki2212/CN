#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 5555

int main(int argc, char *argv[])
{
    int s;
    struct sockaddr_in server_addr;
    char send_buf[100];
    char recv_buf[100];
    int recv_len;
    char message[100];

    if (argc != 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        exit(1);
    }

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Enter message to send: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    strcpy(send_buf, message);

    if (sendto(s, send_buf, strlen(send_buf), 0,
            (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("sendto");
        exit(1);
    }

    recv_len = recvfrom(s, recv_buf, sizeof(recv_buf), 0, NULL, NULL);
    if (recv_len < 0) {
        perror("recvfrom");
        exit(1);
    }

    printf("Received response from server: %s\n", recv_buf);

    close(s);

    return 0;
}