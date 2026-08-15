            // отправляем сообщение с сервера от 1-ого клиента 2-му
            // формируем ответ
            /* char client_response_1[BUFFER_SIZE + 64];
            snprintf(client_response_1, sizeof(client_response_1), "User %d: %s\n", clients[0].client_id, buffer);

            if (send_all(clients[1].client_fd, client_response_1, strlen(client_response_1)) == -1) {
                perror("send");
                close(clients[0].client_fd);
                close(clients[1].client_fd);
                close(listen_fd);
                return 1;
            } */