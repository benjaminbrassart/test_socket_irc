/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_add_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:20:16 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 18:03:26 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <stdlib.h>

void server_add_client(struct client* client)
{
    if (SERVER->clients.size == 0)
        SERVER->clients.begin = client;
    else
        SERVER->clients.end->next = client;
    client->prev = NULL;
    SERVER->clients.end = client;
    client->next = NULL;
    ++SERVER->clients.size;
}
