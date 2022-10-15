/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:20:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 22:45:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# ifndef CLIENT_BUFFER_SIZE
#  define CLIENT_BUFFER_SIZE 1024
# endif

# include <netinet/in.h>
# include <time.h>

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
    struct tm start_time;
    int running;
    unsigned short port;
    char* password;
    int sock_fd;
    struct sockaddr_in addr;
    socklen_t addr_len;
    struct client_list clients;
};

struct command {
    char const* label;
    int operator_only;
    int (*handler)(struct client* sender, char const** args);
};

struct client* client_new();

void server_init(void);
void server_delete(void);
int server_start(void);
void server_loop(void);

void server_add_client(struct client* client);
void server_remove_client(struct client* client);

struct command* get_command(char const* command_name);

int command_help(struct client* sender, char const** args);
int command_join(struct client* sender, char const** args);
int command_leave(struct client* sender, char const** args);
int command_msg(struct client* sender, char const** args);

static struct command const COMMANDS[] = {
    // {"help", 0, command_help},
    // {"join", 0, command_join},
    // {"leave", 0, command_leave},
    // {"msg", 0, command_msg},
};

#endif
