/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:14:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 18:10:23 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct client* client_new(void)
{
    int errnum;
    struct client* client;

    client = calloc(1, sizeof (*client));
    if (client != NULL) {
        client->sock_fd = accept(SERVER->sock_fd, (struct sockaddr*)&SERVER->addr, &SERVER->addr_len);
        if (0 > client->sock_fd) {
            errnum = errno;
            fprintf(stderr, "Fatal: Failed to bind accept connection: %s (%d)\n", strerror(errnum), errnum);
            free(client);
            return NULL;
        }
    }
    return client;
}
