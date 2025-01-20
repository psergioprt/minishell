CC = gcc
NAME = minishell
RM = rm -f
SRCDIR = src
INCDIR = include
LIBFTDIR = Libft
SRC = $(SRCDIR)/minishell.c $(SRCDIR)/nodes_handler.c $(SRCDIR)/utils.c $(SRCDIR)/env_utils.c \
      $(SRCDIR)/env_handler.c $(SRCDIR)/signal_functions.c $(SRCDIR)/parser_handler.c \
      $(SRCDIR)/syntax_parsing.c
LIBFT = $(LIBFTDIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -g -O0 #-fsanitize=address
LFLAGS = -lreadline -L$(LIBFTDIR) -lft #-fsanitize=address
OBJS = ${SRC:.c=.o}

#.SILENT:

$(SRCDIR)%.o: $(SRCDIR)/%.c $(INCDIR)/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFTDIR) clean

valgrind: ${NAME}
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
re: fclean all
