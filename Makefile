NAME=ft_mini_ls
SRC_DIR= ./srcs
INC_DIR= ./includes
SRCS=ft_mini_ls.c
CC=gcc
CFLAGS=-Wall -Wextra -Werror
CFLAGS+=-I $(INC_DIR)
OBJNAMES=$(SRCS:.c=.o)
OBJS=$(addprefix $(SRC_DIR)/,$(OBJNAMES))

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(NAME) $^

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY	: all clean fclean re
