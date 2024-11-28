CC = cc
NAME = minishell
RM = rm -f
SRCDIR = src
INCDIR = include
LIBFTDIR = Libft
SRC = $(SRCDIR)/minishell.c $(SRCDIR)/nodes_handler.c $(SRCDIR)/function_analise.c $(SRCDIR)/echo.c
LIBFT = $(LIBFTDIR)/libft.a
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline -L$(LIBFTDIR) -lft
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

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
re: fclean all
