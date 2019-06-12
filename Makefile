CC = gcc
CFLAGS = -Wall -Wextra -Werror --pedantic -g
NAME = ft_ls
INCLUDES = ./includes/ft_ls.h
SRCS = ft_ls.c
OBJS = ft_ls.o

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft 
	$(CC) $(CFLAGS) $^ -I. ./libft/libft.a -o ft_ls

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I. -c $^

clean:
	rm -rf *.o
	make fclean -C ./libft

fclean: clean
	rm -rf ft_ls

re: fclean all
