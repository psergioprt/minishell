/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:50:35 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/09 17:50:35 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include <fcntl.h>
# include <sys/ioctl.h>

extern int	g_exit_code;

typedef enum e_type //PS: Definition of redirection type and their values
{
	NONE = -1,
	OUTPUT = 1,
	APPEND_OUTPUT,
	INPUT,
	HEREDOC,
	PIPE
}	t_type;

typedef struct s_heredoc
{
	int					fd_heredoc;
	char				*fd_heredoc_path;
	char				*eof;
	bool				eof_quote;
	int					index;
	int					count_hd;
	bool				done;
	bool				targeted;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			print;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	char			*token;
	struct s_node	*next;
	t_type			type; //PS:Redirection type (OUTPUT, APPEND_OUTPUT, ETC)
	char			*target;
}	t_node;

typedef struct s_cmd
{
	t_node			*tokens;
	int				fd[2];
	struct s_cmd	*next;
	int				is_first_command;
}	t_cmd;

typedef struct s_minishell
{
	char			*command;
	char			**envp; //so copia o que tem para usar no execve
	t_node			*tokenlst;
	t_cmd			*commands;
	t_env			*envvars;
	int				exit_status;
	int				has_pipe;
	pid_t			child[1024];
	int				i;
	bool			disable_expand;
	bool			has_error;
	int				env_count;
	char			current_token[1024];
	t_node			*prev_node;
	t_heredoc		*heredoc;
	int				saved_stdout;
	int				saved_stdin;
	bool			unquoted;
	int				interactive;
	bool			is_heredoc;
	int				count;
}	t_minishell;

typedef struct s_parse_context
{
	char		*current_token;
	const char	*input;
	int			index;
	char		quote;
	const char	*exit_status;
	int			m;
}	t_parse_context;

typedef struct s_token_context
{
	char			*current_token;
	int				*i;
	int				*j;
	t_parse_context	*ctx;
}	t_token_context;

t_node		*create_command_node(const char *token, t_type type, \
			t_node **prev_node);
void		add_command_node(t_minishell *mini, const char *token, \
			t_type type, t_node **prev_node);
void		free_list(t_minishell *mini);
void		split_and_add_commands(t_minishell *mini, const char *input);
void		init_variables(t_minishell *mini, t_parse_context *ctx, \
			const char *input, char *current_token);
void		free_envvars(t_minishell *mini);
void		parse_env(t_minishell *mini, char *env[]);
char		*expand_env_var(char *token, t_minishell *mini);
void		copy_env(char *env[], t_minishell *mini);
char		*get_env_value(char *env_name, t_minishell *mini);
void		init_sigaction(int interactive);
void		handle_env_var(t_minishell *mini, t_parse_context *ctx, \
			int *i, int *j);
void		handle_loop_parsers(t_minishell *mini, const char *input, \
			t_token_context *tok_ctx);
void		restore_default_signals(void);

//REDIRECTS_UTILS
void		change_targets(t_minishell *mini);
int			check_access(t_minishell *mini, char *filename, t_type type);
void		redir_or_close_saved(t_minishell *mini);

//PARSE_MALFORMED_OPERATORS
bool		check_malformed_operators(t_minishell *mini, t_parse_context *ctx);

//REDIRECTS_PARSING
bool		validate_redir_syntax(t_minishell *mini, t_parse_context *ctx, \
			int *i, char redir);
bool		count_redir_chars(t_minishell *mini, t_parse_context *ctx, int *i, \
			char redir);
bool		check_redirection_errors(t_minishell *mini, t_parse_context *ctx, \
			int *i);
void		identify_redir_type(t_minishell *mini, char *redir_token);
void		handle_redirectional(t_minishell *mini, t_parse_context *ctx, \
			int *i, int *j);

//REDIR_ERROR_FUNCS
bool		redir_error_message_1(t_minishell *mini, t_parse_context *ctx, \
			int *i);
bool		redir_error_message_2(t_minishell *mini, char *redir);

//SYNTAX_PARSING
void		handle_spaces_quotes(t_minishell *mini, const char *input, \
			t_token_context *tok_ctx);
void		handle_open_close_quotes(t_minishell *mini, t_parse_context *ctx, \
			int *i, int *j);
void		process_quotes(t_minishell *mini, t_parse_context *ctx, int *i, \
			int *j);
void		initialize_quote_handling(t_minishell *mini, t_parse_context *ctx, \
			int *i);
void		process_quoted_content(t_minishell *mini, t_parse_context *ctx, \
			int *i, int *j);

//ADD_EMPTY_TOKEN
void		add_empty_token(t_minishell *mini);
void		add_token_to_list(t_minishell *mini, t_node *new_token);

//PARSE_ENV_NAME_REDIR_CHECK_ERRORS
void		redirect_check_errors_2(t_minishell *mini, char *env_var_name);
void		redirect_check_errors(t_minishell *mini);

//PIPES_CHECK_ERRORS
void		print_pipes_errors(t_minishell *mini);
bool		has_leading_pipe(t_parse_context *ctx);
bool		has_trailing_or_double_pipe(t_parse_context *ctx);
void		check_pipes_errors(t_minishell *mini, t_parse_context *ctx);

//5/2 - Added
void		print_nodes(t_node *command_list);
void		cleanup_fd(t_minishell *mini);

//REDIRECTS_HANDLER
int			handle_redirections(t_minishell *mini);
int			open_file(char *filename, t_type type, t_minishell *mini);
int			handle_redirection_action(int fd, t_node *current);
int			identify_redirection_type(char *token);

//REDIRECTS_CHECK_ERRORS
int			check_redirect_errors_support(t_minishell *mini);
int			check_redirect_errors_support_1(t_minishell *mini);
int			check_redirect_errors(t_minishell *mini);
void		remove_heredoc_token(t_minishell *mini);

//REDIRECTS_SKIP_FUNCTIONS
void		skip_redirection_plus_target_cmd_support(t_node **current, \
			t_node **tmp, t_node **prev, t_node **tokens);
void		skip_redirection_plus_target_cmd(t_cmd *cmd_list);
void		skip_redirection_plus_target_support(t_node **current, \
			t_node **tmp);
void		skip_redirection_plus_target(t_minishell *mini);

//SYNTAX_HELPER
void		handle_sep(t_minishell *mini, t_parse_context *ctx, int *i, int *j);
void		handle_spaces_helper(t_minishell *mini, char *expanded_token, \
			t_token_context *tok_ctx);
void		process_quoted_helper(t_minishell *mini, t_parse_context *ctx, \
			int *i, int *j);
void		handle_double_redir(t_minishell *mini, t_parse_context *ctx, \
			int *i, char **redir_token);

//SIGNALS_FUNCTIONS
void		sigint_handler(int sig);

//NODES_HELPER
void		free_split(char **split);
char		**split_by_ifs(const char *str);

//HANDLE_HEREDOC
void		close_fds(t_minishell *mini, t_heredoc *tmp_hd, char *line);
void		redir_error_close(t_minishell *mini);
void		process_heredoc_token(t_minishell *mini, t_node **current_token, \
			t_node **prev_token);
void		support_heredoc_token_tokens(t_minishell *mini);
void		process_heredoc_command(t_minishell *mini, t_node **current_cmd, \
			t_node **prev_cmd);
void		support_heredoc_token_commands(t_minishell *mini);
void		remove_heredoc_token(t_minishell *mini);
void		support_heredoc(t_heredoc *tmp_hd, t_minishell *mini, int *prev_fd);
void		heredoc(t_minishell *mini, int *prev_fd);

//HANDLE_HEREDOC2
void		support_fill_fr_heredoc(t_heredoc *tmp_hd, t_minishell *mini);
int			open_heredoc(t_heredoc *tmp_hd);
void		close_fds(t_minishell *mini, t_heredoc *tmp_hd, char *line);
int			fill_fd_heredoc(t_heredoc *tmp_hd, t_minishell *mini);
void		handle_child_process(t_minishell *mini, int *prev_fd);

//HANDLE_HEREDOC3
void		initialize_heredoc(t_minishell *mini, t_node *tmp);
void		append_heredoc(t_minishell *mini, t_node *tmp);
void		save_heredoc_info(t_minishell *mini);

//HEREDOC_UTILS
void		handle_ctrl_c_hd(t_minishell *mini);
void		handle_heredoc_signal(int signal);
void		set_signals_to_here_doc(void);
char		*ft_strjoin_free(char *s1, const char *s2);
int			check_malloc(void *ptr);

//HEREDOC_UTILS2
void		clear_heredoc_list(t_minishell *mini);
void		include_hd_path(t_minishell *mini);
int			find_next_env(char *line);
char		*append_expanded_env(t_minishell *mini, char *result, char **pline, \
			int pos);

//HEREDOC_UTILS3
void		init_heredoc(t_minishell *mini);
char		*expand_env_vars_in_line(t_minishell *mini, char *line);
void		check_hd_expand(char **line, t_minishell *mini);
void		handle_heredoc_child(t_heredoc *tmp_hd, t_minishell *mini);
int			has_heredoc(t_minishell *mini);

//FUNCTION_ANALISE
int			first_token(t_minishell *mini);
void		exec_cmds(t_minishell *mini);
void		execute(t_minishell *mini, t_cmd *cmdlst);

//SPLIT_INTO_COMMANDS
void		split_commands(t_minishell *mini);

//ECHO
int			custom_echo(t_minishell *mini);

//Splits
void		parse_env(t_minishell *node, char *env[]);
void		copy_env(char *env[], t_minishell *mini);

//EXEC
int			execute_execve(t_minishell *mini);

//EXEC_UTILS
char		*find_path(t_minishell *mini);
char		*fallback_path(t_minishell *mini);
char		**get_argv(t_minishell *mini, int i, t_node *node);
void		get_command(t_minishell *mini);
int			execpath_error(char *path);

//EXEC_UTILS2
int			handle_direct_path(t_minishell *mini, char **argv);
void		feel_signals(t_minishell *mini, int status);
int			handle_search_path(t_minishell *mini, t_node *node, \
			char **pathname);

//ERROR
void		ft_error(char *error_msg, t_minishell *mini);
void		free_commands(t_cmd *commands);
void		free_tokens(t_node *tokens);

//CD
int			custom_cd(t_minishell *mini);

//ENV
int			custom_env(t_minishell *mini);

//EXPORT
int			custom_export(t_minishell *mini);
//int		replace_value(t_env *found_env, char *value);

//EXPORT_UTILS
char		*skip_plus(char *str);
int			export_no_args(t_minishell *mini);
t_env		*export_args(char *var);

//UNSET
int			custom_unset(t_minishell *mini);

//KEY_UTILS
int			count_node(t_minishell *mini);
t_env		*find_key(t_minishell *mini, char *key);
int			check_valid_key(char *str, bool *cat);
int			replace_env_value(t_env *found_env, char *value);

//PWD
int			custom_pwd(t_minishell *mini);

//EXIT
int			custom_exit(t_minishell *mini);

//EXIT_UTILS
bool		m_long(char *str);
int			is_num(char *str);
long long	ft_atoll(const char *str);

//PIPES
void		create_pipes(t_cmd *cmd);
void		redir_fds(int redir, int local);
void		wait_childs(t_minishell *mshell, int n_cmds);
int			get_ncmds(t_cmd *cmd);
pid_t		create_pid(void);

#endif