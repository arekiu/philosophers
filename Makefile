# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmidt <aschmidt@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 15:38:07 by aschmidt          #+#    #+#              #
#    Updated: 2024/08/01 15:45:06 by aschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CCFLAGS = -Wall -Wextra -Werror -pthread

SRC	= $(addprefix src/, main.c check_input.c)

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
