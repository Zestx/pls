CC = gcc
CFLAGS = -Wall -Wextra --pedantic -g 
NAME = ft_ls
INCLUDES = ./includes/ft_ls.h
SRCS = ft_ls.c parse.c util.c sort_args.c ll_util.c list.c display.c getstat.c sort_ll.c util2.c print_args.c
OBJS = ft_ls.o parse.o util.o sort_args.o ll_util.o list.o display.o getstat.o sort_ll.o util2.o print_args.o

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
