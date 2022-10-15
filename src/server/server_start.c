/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:12:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 23:02:30 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "irc.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void _setup_time(void);

int server_start()
{
    int errnum;
    char timebuff[128];

    _setup_time();
    strftime(timebuff, sizeof (timebuff), "%a %d %Y %T", &SERVER->start_time);

    printf("ft_irc server version %s\nBuild date: %s\nStart date: %s\n", FT_IRC_VERSION, FT_IRC_BUILD_DATE, timebuff);

    SERVER->sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (0 == SERVER->sock_fd) {
        errnum = errno;
        fprintf(stderr, "Fatal: Failed to create socket: %s (%d)\n", strerror(errnum), errnum);
        return 0;
    }

    SERVER->addr.sin_family = AF_INET;
    SERVER->addr.sin_addr.s_addr = INADDR_ANY;
    SERVER->addr.sin_port = htons(SERVER->port);

    if (0 > bind(SERVER->sock_fd, (struct sockaddr*)&SERVER->addr, sizeof (SERVER->addr))) {
        errnum = errno;
        fprintf(stderr, "Fatal: Failed to bind socket on port: %s (%d)\n", strerror(errnum), errnum);
        return 0;
    }

    // TODO add listen to read_fds
    if (0 > listen(SERVER->sock_fd, 3)) {
        errnum = errno;
        fprintf(stderr, "Fatal: Failed to listen: %s (%d)\n", strerror(errnum), errnum);
        return 0;
    }

    printf("Listening on port %d\n", SERVER->port);

    SERVER->running = 1;

    while (SERVER->running) {
        server_loop();
    }
    return 1;
}

static void _setup_time(void)
{
    time_t current_time;

    time(&current_time);
    SERVER->start_time = *localtime(&current_time);
}
