/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_remove_client.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:02:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 18:07:00 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <stdlib.h>

void server_remove_client(struct client* client)
{
    struct client* prev;
    struct client* next;

    prev = client->prev;
    next = client->next;

    if (prev == NULL)
        SERVER->clients.begin = next;
    else
        prev->next = next;
    if (next == NULL)
        SERVER->clients.end = prev;
    else
        next->prev = prev;
    --SERVER->clients.size;
}
