/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:26:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 21:36:14 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void server_loop(void) {
    fd_set read_fds;
    // fd_set write_fds;
    int pool_fd;
    int max_pool_fd;
    int rd;
    int errnum;
    struct client* it;
    struct client* fast;
    struct client* new_client;
    char buffer[CLIENT_BUFFER_SIZE];
    FD_ZERO(&read_fds);
    FD_SET(SERVER->sock_fd, &read_fds);
    max_pool_fd = SERVER->sock_fd;

    it = SERVER->clients.begin;
    while (it != NULL) {
        FD_SET(it->sock_fd, &read_fds);
        if (it->sock_fd > max_pool_fd)
            max_pool_fd = it->sock_fd;
        it = it->next;
    }

    pool_fd = select(max_pool_fd + 1, &read_fds, NULL, NULL, NULL);

    errnum = errno;
    if (0 > pool_fd) {
        if (EINTR != errnum)
            fprintf(stderr, "Fatal: Failed to pool connections: %s (%d)\n", strerror(errnum), errnum);
        SERVER->running = 0;
        return;
    }

    if (FD_ISSET(SERVER->sock_fd, &read_fds)) {
        // incoming connection
        new_client = client_new();
        if (new_client == NULL) {
            errnum = errno;
            fprintf(stderr, "Fatal: Failed to pool connections: %s (%d)\n", strerror(errnum), errnum);
            SERVER->running = 0;
            return;
        }
        server_add_client(new_client);
        send(new_client->sock_fd, "Hello World!\n", 13, 0);
        printf("New connection!\n");
    }

    it = SERVER->clients.begin;
    while (it != NULL) {
        fast = it->next;
        if (FD_ISSET(it->sock_fd, &read_fds)) {
            rd = recv(it->sock_fd, buffer, sizeof (buffer), 0);
            if (0 == rd) {
                printf("Closing connection!\n");
                close(it->sock_fd);
                server_remove_client(it);
                free(it);
            } else {
                printf("| %*s\n", rd, buffer);
                send(it->sock_fd, "OK\n", 3, 0);
            }
        }
        it = fast;
    }
}
