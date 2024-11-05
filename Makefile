CC = cc
NAME = minishell
RM = rm -f
SRCDIR = src
INCDIR = include
SRC = $(SRCDIR)/minishell.c
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
OBJS = ${SRC/.c=.o}
all: $(NAME)
$(NAME): $(OBJS) $(INCDIR)/minishell.h
	$(CC) $(CFLAGS) $(OBJS) $(SRCDIR)/minishell.c -o $(NAME) $(LFLAGS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
