#ifndef NET_COMMON_H
#define NET_COMMON_H

#include <stddef.h>
#include <sys/types.h>

int send_all(int socket_fd, const char *buf, size_t len_buf);
ssize_t recv_line(int socket_fd, char *buf, size_t len_buf);

#endif