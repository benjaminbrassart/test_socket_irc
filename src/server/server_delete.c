/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:21:00 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 18:39:01 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void server_delete(void) {
    struct client* it;
    struct client* fast;
    int dummy;

    dummy = 1;
    setsockopt(SERVER->sock_fd, SOL_SOCKET, SO_REUSEADDR, &dummy, sizeof (int));
    close(SERVER->sock_fd);
    it = SERVER->clients.begin;
    while (it != NULL) {
        fast = it->next;
        free(it);
        it = fast;
    }
    free(SERVER->password);
}
