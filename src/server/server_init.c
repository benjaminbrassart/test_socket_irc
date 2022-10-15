/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:26:14 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 18:20:25 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <stdio.h>
#include <signal.h>

static void _handle_sig(int sig);

void server_init(struct server* server)
{
    unsigned char* dst;
    size_t n;

    dst = (unsigned char*)server;
    n = 0;
    while (n < sizeof (*server))
        dst[n++] = 0;
    signal(SIGINT, _handle_sig);
}

static void _handle_sig(int sig)
{
    signal(sig, SIG_DFL);
    SERVER->running = 0;
}
