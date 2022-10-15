/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:16:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 21:19:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

#include <string.h>

struct command* get_command(char const* command_name) {
    size_t i;

    i = 0;
    while (i < (sizeof (COMMANDS) / sizeof (*COMMANDS))) {
        if (strcmp(COMMANDS[i].label, command_name) == 0)
            return &COMMANDS[i];
        ++i;
    }
    return NULL;
}
