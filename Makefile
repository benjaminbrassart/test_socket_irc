# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 15:09:51 by bbrassar          #+#    #+#              #
#    Updated: 2022/10/15 21:33:20 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_irc

CC = cc
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -c
CFLAGS += -MMD -MP
CFLAGS += -I.
CFLAGS += -g3

RM = rm -f

DIR_SRC = src
DIR_OBJ = obj

SRC += main.c
SRC += server/server_init.c
SRC += server/server_start.c
SRC += server/server_delete.c
SRC += server/server_loop.c
SRC += server/server_add_client.c
SRC += server/server_remove_client.c
SRC += client/client_new.c
OBJ = $(SRC:%.c=$(DIR_OBJ)/%.o)
DEP = $(OBJ:.o=.d)

# LDLIBS +=
# LDFLAGS +=

_LD = $(LDLIBS) $(LDFLAGS)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(_LD)

$(OBJ): $(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

-include $(DEP)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) -r $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
