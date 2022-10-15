/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:20:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 18:22:55 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# ifndef CLIENT_BUFFER_SIZE
#  define CLIENT_BUFFER_SIZE 1024
# endif

# include <netinet/in.h>

struct server;

extern struct server* SERVER;

struct client {
    int sock_fd;
    struct client* prev;
    struct client* next;
};

struct client_list {
    struct client* begin;
    struct client* end;
    size_t size;
};

struct server {
    int running;
    unsigned short port;
    char* password;
    int sock_fd;
    struct sockaddr_in addr;
    socklen_t addr_len;
    struct client_list clients;
};

struct client* client_new();

void server_init();
void server_delete();
int server_start();

void server_add_client(struct client* client);
void server_remove_client(struct client* client);

#endif
