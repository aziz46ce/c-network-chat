
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 8080

int main(int argc, char *argv[]) {
    int sockfd;
    int port = DEFAULT_PORT;
    char message[BUFFER_SIZE];
    const char *ip = "127.0.0.1";
    struct sockaddr_in server_addr;

    if (argc > 3) {
        fprintf(stderr, "Usage: %s [IP] [PORT]\n", argv[0]);
        return 1;
    }

    if (argc >= 2) {
        ip = argv[1];
    }

    if (argc == 3) {
        char *end;
        errno = 0;
        long value = strtol(argv[2], &end, 10);

        if (errno != 0 || end == argv[2] ||
            *end != '\0' || value < 1 || value > 65535) {
            fprintf(stderr, "Invalid port number\n");
            return 1;
        }

        port = (int)value;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons((unsigned short)port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IPv4 address\n");
        close(sockfd);
        return 1;
    }

    printf("UDP Sender Started\n");
    printf("Destination: %s:%d\n", ip, port);
    printf("Type 'exit' to quit.\n");

    while (1) {
        printf("Enter message: ");
        fflush(stdout);

        if (fgets(message, sizeof(message), stdin) == NULL) {
            break;
        }

        size_t len = strlen(message);

        if (len > 0 && message[len - 1] == '\n') {
            message[--len] = '\0';
        } else if (len == sizeof(message) - 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fprintf(stderr, "Message too long\n");
            continue;
        }

        if (strcmp(message, "exit") == 0) {
            break;
        }

        if (len == 0) {
            continue;
        }

        if (sendto(sockfd, message, len, 0,
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

