NAME=philo_one
CC=gcc
FLAG=-Wall -Wextra -Werror
SRCS=	main.c \
		monitor_thread.c \
		philo_fork.c \
		print_log.c \
		timestamp.c \
		utils.c

OBJS= ${SRCS:.c=.o}
HEADER= -I.

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(FLAG) $(HEADER) $^ -o $(NAME)

%.o: %.c
	$(CC) $(FLAG) $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all