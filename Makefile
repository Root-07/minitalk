# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 12:44:01 by ael-amin          #+#    #+#              #
#    Updated: 2023/01/10 12:49:51 by ael-amin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minitalk.h

NAME_BONUS = minitalk.h

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all : server client

bonus: server_bonus client_bonus

server: server.c minitalk_utils.c $(NAME)
	$(CC) $(CFLAGS) server.c minitalk_utils.c -o server

client: client.c minitalk_utils.c $(NAME)
	$(CC) $(CFLAGS) client.c minitalk_utils.c -o client

server_bonus: server_bonus.c minitalk_utils.c $(NAME_BONUS)
	$(CC) $(CFLAGS) server_bonus.c minitalk_utils.c -o server_bonus

client_bonus: client_bonus.c minitalk_utils.c $(NAME_BONUS)
	$(CC) $(CFLAGS)  client_bonus.c minitalk_utils.c -o client_bonus

clean:

fclean : clean
	@rm -f server server_bonus client client_bonus

re : fclean all
