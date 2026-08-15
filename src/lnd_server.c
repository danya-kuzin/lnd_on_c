#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <sys/select.h>
#include <stdlib.h>
#include "net_common.h"
#include "game.h"
#include "server_command_handler.h"

#define SERVER_PORT 50500
#define BACKLOG 8
#define BUFFER_SIZE 256
#define MAX_CLIENTS 4

int main(void)
{
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_fd == -1) {
        perror("socket");
        return 1;
    }

    int opt = 1;

    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(listen_fd);
        return 1;
    }

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // т.к сервер и клиент пока будут внутри одной машины
    // INADDR_LOOPBACK возвращает 127.0.0.1 - адрес моей машины
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // привязываем к сокету адрес и порт через bind
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(listen_fd);
        return 1;
    }

    // переводим сервер в режим слушания
    if (listen(listen_fd, BACKLOG) == -1) {
        perror("listen");
        close(listen_fd);
        return 1;
    }

    printf("Server socket created with fd=%d, bound to 127.0.0.1:%d and listen\n",  listen_fd, SERVER_PORT);

    // создаем массив всех клиентов
    struct Client clients[MAX_CLIENTS];

    // впускаем первого клиента
    printf("Waiting for client_1...\n");

    // принимаем соединение и добавляем сокет для общения с клиентом
    clients[0].client_fd = accept(listen_fd, NULL, NULL);
    clients[0].client_id = 1;

    if (clients[0].client_fd == -1) {
        perror("accept");
        close(listen_fd);
        return 1;
    }

    printf("Client_%d connected, client_fd=%d\n", clients[0].client_id, clients[0].client_fd);

    // впускаем второго клиента
    printf("Waiting for client_2...\n");

    // принимаем соединение и добавляем сокет для общения с клиентом
    clients[1].client_fd = accept(listen_fd, NULL, NULL);
    clients[1].client_id = 2;
    if (clients[1].client_fd == -1) {
        perror("accept");
        close(clients[0].client_fd);
        close(listen_fd);
        return 1;
    }
    
    printf("Client_%d connected, client_fd=%d\n\n\n", clients[1].client_id, clients[1].client_fd);

    // инициализируем игру
    struct GameState game;
    game_init(&game, 2); // в игре пока фиксированное кол-ва игроов - 2
    int client_count = 2;

    while (true) {
        // создаем полное множество fd
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(clients[0].client_fd, &read_fds);
        FD_SET(clients[1].client_fd, &read_fds);

        int max_fd = clients[0].client_fd;
        if (clients[0].client_fd < clients[1].client_fd) {
            max_fd = clients[1].client_fd;
        }

        // смотрим из каких fd можно читать
        int ready_count = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (ready_count == -1) {
            perror("select");
            close(listen_fd);
            close(clients[0].client_fd);
            close(clients[1].client_fd);
            return 1;
        }

        
        // если можно считать из сокетного буфера первого клиента
        if (FD_ISSET(clients[0].client_fd, &read_fds)) {
            char buffer[BUFFER_SIZE];
            ssize_t bytes_received = recv_line(clients[0].client_fd, buffer, sizeof(buffer));

            if (bytes_received == -1) {
                perror("recv");
                close(listen_fd);
                close(clients[0].client_fd);
                close(clients[1].client_fd);
                return 1;
            }

            if (bytes_received == 0) {
                printf("No recived bytes \n");
                break;
            }
            else {
                printf("Message from client_%d with fd=%d : %s", clients[0].client_id, clients[0].client_fd, buffer);
            }

            printf("\nSent response to client_%d\n\n", clients[0].client_id);
            
            // отправляем команду в распределитель команд
            server_handle_command(&game, clients, client_count, 0, buffer);

            if (strcmp(buffer, "quit") == 0) {
                printf("The client_%d has completed the process\n", clients[0].client_id);
                break;
            }
        }

        // если можно считать из сокетного буфера второго клиента
        if (FD_ISSET(clients[1].client_fd, &read_fds)) {
            char buffer[BUFFER_SIZE];
            ssize_t bytes_received = recv_line(clients[1].client_fd, buffer, sizeof(buffer));

            if (bytes_received == -1) {
                perror("recv");
                close(listen_fd);
                close(clients[0].client_fd);
                close(clients[1].client_fd);
                return 1;
            }

            if (bytes_received == 0) {
                printf("No recived bytes \n");
                continue;
            }
            else {
                printf("Message from client_%d with fd=%d : %s", clients[1].client_id, clients[1].client_fd, buffer);
            }

            printf("\nSent response to client_%d\n\n", clients[1].client_id);

            // отправляем команду в распределитель команд
            server_handle_command(&game, clients, client_count, 1, buffer);

            if (strcmp(buffer, "quit") == 0) {
                printf("The client_%d has completed the process\n", clients[1].client_id);
                break;
            }
        }

    }

    close(listen_fd);
    close(clients[0].client_fd);
    close(clients[1].client_fd);

    return 0;
}