CC = cc
NAME = minishell
RM = rm -f
SRCDIR = src
INCDIR = include
LIBFTDIR = Libft
SRC = $(SRCDIR)/minishell.c $(SRCDIR)/nodes_handler.c $(SRCDIR)/function_analise.c $(SRCDIR)/echo.c \
	  $(SRCDIR)/exec.c $(SRCDIR)/exec_utils.c $(SRCDIR)/exec_utils2.c $(SRCDIR)/error.c $(SRCDIR)/cd.c $(SRCDIR)/env.c \
	  $(SRCDIR)/export.c $(SRCDIR)/unset.c $(SRCDIR)/utils.c $(SRCDIR)/pwd.c $(SRCDIR)/pipes.c $(SRCDIR)/key_utils.c \
	  $(SRCDIR)/env_utils.c $(SRCDIR)/env_handler.c $(SRCDIR)/signal_functions.c $(SRCDIR)/parser_handler.c \
	  $(SRCDIR)/syntax_parsing.c $(SRCDIR)/exit.c $(SRCDIR)/exit_utils.c $(SRCDIR)/split_into_commands.c \
	  $(SRCDIR)/handle_heredoc.c $(SRCDIR)/heredoc_utils.c $(SRCDIR)/heredoc_utils2.c $(SRCDIR)/heredoc_utils3.c \
	  $(SRCDIR)/redirects_handler.c $(SRCDIR)/nodes_helper.c $(SRCDIR)/syntax_helper.c $(SRCDIR)/handle_heredoc_2.c \
	  $(SRCDIR)/handle_heredoc_3.c $(SRCDIR)/redirects_check_errors.c $(SRCDIR)/redirects_skip_functions.c \
	  $(SRCDIR)/remove_heredoc_token.c $(SRCDIR)/export_utils.c $(SRCDIR)/pipes_check_errors.c \
	  $(SRCDIR)/parse_env_name_redir_check_errors.c $(SRCDIR)/add_empty_token.c $(SRCDIR)/redirects_parsing.c \
	  $(SRCDIR)/redir_error_funcs.c $(SRCDIR)/parse_malformed_operators.c $(SRCDIR)/redirects_utils.c
LIBFT = $(LIBFTDIR)/libft.a
CFLAGS = -Wall -Wextra -Werror 	-g -O0# -fsanitize=address
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
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --gen-suppressions=all --track-origins=yes --trace-children=yes -s ./minishell  
fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
re: fclean all
