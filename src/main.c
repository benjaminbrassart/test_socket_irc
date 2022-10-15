/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:18:22 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 22:45:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct server* SERVER;

static inline char* _basename(char const* str);
static inline int _parse_ushort(char const* s, unsigned short* out);

int main(int argc, char *argv[]) {
    struct server server;
    int res;

    if (3 != argc) {
        fprintf(stderr, "Usage: %s <port> <password>\n", _basename(argv[0]));
        return EXIT_FAILURE;
    }
    SERVER = &server;
    server_init();
    if (0 == _parse_ushort(argv[1], &SERVER->port)) {
        return EXIT_FAILURE;
    }
    SERVER->password = strdup(argv[2]);
    if (NULL == SERVER->password) {
        fprintf(stderr, "Fatal: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    res = server_start();
    server_delete();
    if (0 == res)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static inline char* _basename(char const* str) {
    char const* s = str;
    char const* p = s;

    while (*p != '\0') {
        if (*p == '/')
            s = p;
        ++p;
    }
    if (s != str)
        ++s;
    return (char*)s;
}

static inline int _parse_ushort(char const* s, unsigned short* out) {
    unsigned int value;

    value = 0;
    while (isdigit(*s)) {
        value = value * 10 + *s - '0';
        if (value == 0 || value > (1 << (sizeof (*out) * 8)))
            break;
        ++s;
    }
    if (*s == '\0')
    {
        *out = (unsigned short)value;
        return 1;
    }
    fprintf(stderr, "Fatal: Invalid port\n");
    return 0;
}
