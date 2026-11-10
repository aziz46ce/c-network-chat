
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
    int sockfd;
    char message[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1",
                  &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IP address\n");
        close(sockfd);
        return 1;
    }

    printf("UDP Sender Started!\n");
    printf("Type 'exit' to quit.\n");

    while (1) {
        printf("Enter message: ");

        if (fgets(message, sizeof(message), stdin) == NULL) {
            break;
        }

        message[strcspn(message, "\n")] = '\0';

        if (strcmp(message, "exit") == 0) {
            break;
        }

        if (sendto(sockfd, message, strlen(message),
                   0,
                   (struct sockaddr *)&server_addr,
                   sizeof(server_addr)) < 0) {
            perror("Send failed");
            break;
        }

        printf("Message sent!\n");
    }

    close(sockfd);
    return 0;
}
