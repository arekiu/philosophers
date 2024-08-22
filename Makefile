# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 15:38:07 by aschmidt          #+#    #+#              #
#    Updated: 2024/08/22 11:27:44 by aschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CCFLAGS = -Wall -Wextra -Werror -pthread

SRC	= $(addprefix src/, main.c input_utils.c program_utils.c simulation.c philo_utils.c)

OBJS	= $(SRC:%.c=%.o)

NAME	= philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
