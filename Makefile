SERVER = server

CLIENT = client

SRCS = src/ft_atoi.c src/ft_itoa.c src/ft_server.c

SRCSB = src/ft_atoi.c src/ft_client.c src/ft_itoa.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

HEADER = minitalk.h

OBJS = $(SRCS:.c=.o)

OBJSB = $(SRCSB:.c=.o)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

all : $(SERVER) $(CLIENT)

$(SERVER): $(OBJS) $(HEADER)
	$(CC) $(FLAGS) -o $(SERVER) $(OBJS)

$(CLIENT): $(OBJSB) $(HEADER)
	$(CC) $(FLAGS) -o $(CLIENT) $(OBJSB)

clean :
	rm -rf $(OBJS)
	rm -rf $(OBJSB)

fclean : clean
	rm -rf $(SERVER) $(CLIENT)

re : fclean all