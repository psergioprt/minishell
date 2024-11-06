CC = cc
NAME = minishell
RM = rm -f
SRCDIR = src
INCDIR = include
SRC = $(SRCDIR)/minishell.c
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
OBJS = ${SRC:.c=.o}

$(SRCDIR)%.o: $(SRCDIR)/%.c $(INCDIR)/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
