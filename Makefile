CC = cc
NAME = minitalk
SERVER_NAME = server
CLIENT_NAME = client
PREFIX = 
COMPILE_FLAGS = -Wall -Wextra -Werror
LINK_LIBFT_FLAGS = -lft -Llibft
INCLUDES = -Ilibft

all: $(NAME)

pre:
	$(PREFIX)cd libft && make all

SERVER_SRCS = server.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_SRCS = client.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

$(NAME): $(SERVER_OBJS) $(CLIENT_OBJS)
	$(PREFIX)$(CC) $(SERVER_OBJS) -o $(SERVER_NAME) $(LINK_LIBFT_FLAGS)
	$(PREFIX)$(CC) $(CLIENT_OBJS) -o $(CLIENT_NAME) $(LINK_LIBFT_FLAGS)

$(SERVER_OBJS): %.o: %.c
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $< -o $@ -g $(INCLUDES) -c

$(CLIENT_OBJS): %.o: %.c
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $< -o $@ -g $(INCLUDES) -c

preclean:
	$(PREFIX)cd libft && make clean

prefclean:
	$(PREFIX)cd libft && make fclean

clean: preclean
	$(PREFIX)rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean prefclean
	$(PREFIX)rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

PHONY: all pre preclean clean fclean re
