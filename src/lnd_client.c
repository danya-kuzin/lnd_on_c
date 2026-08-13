#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "net_common.h"

#define SERVER_PORT 50500
#define BUFFER_SIZE 256

int main(void /* по вайфаю int argc, char *argv[]*/)
{   

    // сокетный буфер обмена между машинами
    char buffer[BUFFER_SIZE];

    // переменная если клиент пишет quit
    bool quit_flag = false;

    printf("Client started\n");

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    // описываем структуру серверного адреса, чтобы к нему подключился клиент
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    /* настройка подключения по вайфаю
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        return 1;
    }

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid server IP\n");
        close(server_fd);
        return 1;
    }*/

    // переводим созданный сокет в режим connected
    if (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(server_fd);
        return 1;
    }

    printf("Connected to server, fd=%d\n", server_fd);

    while (quit_flag == false) {
        printf("\nEnter message: ");
        fflush(stdout);

        // создаем полное множество fd
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(server_fd, &read_fds);

        int max_fd = STDIN_FILENO;
        if (STDIN_FILENO < server_fd) {
            max_fd = server_fd;
        }

        // смотрим из каких fd можно читать
        int ready_count = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (ready_count == -1) {
            perror("select");
            close(STDIN_FILENO);
            close(server_fd);
            return 1;
        }
        
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            // читаем строку из терминала
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("No input \n");
                close(server_fd);
                return 1;
            }

            // отправляем буфер на сервер
            if (send_all(server_fd, buffer, strlen(buffer)) == -1) {
                perror("send");
                close(server_fd);
                return 1;

            }

            printf("Sent message to server\n");

            // проверяем на то, что клиент написал quit
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strcmp(buffer, "quit") == 0) {
                printf("You have completed the process\n");
                quit_flag = true;
            }
        }

        if (FD_ISSET(server_fd, &read_fds)) {
            /* принимаем ответ от сервера о том, что наше сообщение дошло
            ssize_t bytes_received = recv_line(server_fd, buffer, sizeof(buffer) - 1);
            if (bytes_received == -1) {
                perror("recv");
                close(server_fd);
                return 1;
            }

            if (bytes_received == 0) {
                printf("No response from server\n");
            } else {
                printf("Server response: %s \n", buffer);
            }*/

            // принимаем сообщение от другого клиента, прошедшее через сервер
            printf("\n");
            ssize_t bytes_received = recv_line(server_fd, buffer, sizeof(buffer) - 1);
            if (bytes_received == -1) {
                perror("recv");
                close(server_fd);
                return 1;
            }

            if (bytes_received == 0) {
                printf("No response from server\n");
                quit_flag = true;
            } else {
                printf("%s \n", buffer);
            }
        }
    }

    close(server_fd);

    return 0;
}