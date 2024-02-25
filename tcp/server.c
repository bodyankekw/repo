#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void handle_client(int newsockfd) {
    int n;
    char line[1000];

    while ((n = read(newsockfd, line, 999)) > 0) {
        printf("%d: %s", newsockfd, line);
        if ((n = write(newsockfd, line, strlen(line) + 1)) < 0) {
            perror(NULL);
            close(newsockfd);
            exit(1);
        }
    }
    if (n < 0) {
        perror(NULL);
        close(newsockfd);
        exit(1);
    }
    close(newsockfd);
}

int main() {
    int sockfd, newsockfd;
    int clilen;
    struct sockaddr_in servaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror(NULL);
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    while (1) {
        clilen = sizeof(cliaddr);

        if ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror(NULL);
            close(sockfd);
            close(newsockfd);
            exit(1);
        } else if (pid == 0) { // Child process
            close(sockfd);
            handle_client(newsockfd);
            exit(0);
        } else { // Parent process
            close(newsockfd);
        }
    }
}