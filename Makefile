CC = gcc
CFLAGS = -Wall -Wextra --pedantic 
NAME = ft_ls
INCLUDES = ./includes/ft_ls.h
SRCS = ft_ls.c parse.c util.c
OBJS = ft_ls.o parse.o util.o

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
