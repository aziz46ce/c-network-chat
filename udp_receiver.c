
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sockfd;
    int port = DEFAULT_PORT;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [PORT]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        char *end;
        errno = 0;
        long value = strtol(argv[1], &end, 10);

        if (errno != 0 || end == argv[1] ||
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
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    printf("UDP Receiver Started\n");
    printf("Listening on port %d...\n", port);
    fflush(stdout);

    while (1) {
        socklen_t addr_len = sizeof(client_addr);

        ssize_t n = recvfrom(
            sockfd,
            buffer,
            BUFFER_SIZE - 1,
            0,
            (struct sockaddr *)&client_addr,
            &addr_len
        );

        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("Receive failed");
            break;
        }

        buffer[n] = '\0';

        char sender_ip[INET_ADDRSTRLEN];

        if (inet_ntop(AF_INET,
                      &client_addr.sin_addr,
                      sender_ip,
                      sizeof(sender_ip)) == NULL) {
            perror("Address conversion failed");
            continue;
        }

        printf("[%s:%u] %s\n",
               sender_ip,
               (unsigned int)ntohs(client_addr.sin_port),
               buffer);
        fflush(stdout);
    }

    close(sockfd);
    return 0;
}
