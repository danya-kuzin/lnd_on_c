#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include "net_common.h"

// функция для полной отправки сообщения
int send_all(int socket_fd, const char *buf, size_t len_buf) {
    size_t total_sent = 0;

    while (total_sent < len_buf) {
        ssize_t bytes_sent = send(socket_fd, buf + total_sent, len_buf - total_sent, 0);

        // возвращаем -1 чтобы потом уже основная часть программы 
        // сделала close и perror
        if (bytes_sent <= 0) {
            return -1;
        }

        total_sent += (size_t)bytes_sent;
    }

    return 0;
}

// функция для полного принятия сообщения
ssize_t recv_line(int socket_fd, char *buf, size_t len_buf) {
    size_t cur_len_buf = 0;
    ssize_t flag_cur_byte;
    char cur_char;

    while (cur_len_buf < len_buf) {
        flag_cur_byte = recv(socket_fd, &cur_char, 1, 0);

        if (flag_cur_byte == 0) {
            if (cur_len_buf == 0) {
                return 0;
            }
            break;
        }

        if (flag_cur_byte == -1) {
            return -1;
        }

        if (cur_char == '\n') {
            break;
        }

        buf[cur_len_buf] = cur_char;
        cur_len_buf++;

    }

    buf[cur_len_buf] = '\0';
    return (ssize_t)cur_len_buf;
}