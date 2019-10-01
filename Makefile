# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srobin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 19:37:57 by srobin            #+#    #+#              #
#    Updated: 2019/10/01 17:17:02 by qbackaer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = ft_ls
INCLUDES = ./includes/ft_ls.h
SRCS = ft_ls.c parse.c util.c sort_args.c ll_util.c list.c display.c getstat.c sort_ll.c util2.c print_args.c ll_util2.c \
	   util_time.c display2.c args_max.c ll_util3.c sort_args2.c display3.c
OBJS = ft_ls.o parse.o util.o sort_args.o ll_util.o list.o display.o getstat.o sort_ll.o util2.o print_args.o ll_util2.o \
	   util_time.o display2.o args_max.o ll_util3.o sort_args2.o display3.o

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft 
	$(CC) $(CFLAGS) $^ -I inc/ ./libft/libft.a -o ft_ls

$(OBJS): $(addprefix src/,$(SRCS))
	$(CC) $(CFLAGS) -I inc/ -c $^

clean:
	rm -rf *.o
	make fclean -C ./libft

fclean: clean
	rm -rf ft_ls

re: fclean all
