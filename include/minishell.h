/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:45 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/29 17:50:15 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
#include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

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
}	t_node;

typedef struct s_cmd
{
	t_node			*tokens;
	int				fd[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	char			*command;
	char			**envp; //so copia o que tem para usar no execve
	t_node			*tokenlst;
	t_cmd			*commands;
	t_env			*envvars;
	int				exit_status; //TODO init
	int				has_pipe;
	bool			disable_expand;
	bool			has_error;
	char			*last_command_out; //TODO fazer logica de pipe, e necessario isto?
	int				env_count;
	char			current_token[1024];
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

t_node		*create_command_node(const char *command);
void		add_command_node(t_minishell *mini, const char *command);
void		free_list(t_minishell *mini);
void		split_and_add_commands(t_minishell *mini, const char *input);
void		init_variables(t_minishell *mini, t_parse_context *ctx, \
			const char *input, char *current_token);
void		cleanup_readline(void);
void		free_envvars(t_minishell *mini);
void		parse_env(t_minishell *mini, char *env[]);
char		*expand_env_var(char *token, t_minishell *mini);
void		copy_env(char *env[], t_minishell *mini);
char		*get_env_value(char *env_name, t_minishell *mini);
void		print_envvar(t_minishell *mini);
void		init_sigaction(void);
void		handle_env_var(t_minishell *mini, t_parse_context *ctx, int *i, int *j);
void		handle_loop_parsers(t_minishell *mini, const char *input, \
			t_token_context *tok_ctx);
void		handle_spaces_quotes(t_minishell *mini, const char *input, \
			t_token_context *tok_ctx);
void		handle_open_close_quotes(t_minishell *mini, \
			t_parse_context *ctx, int *i, int *j);
void		handle_sep(t_minishell *mini, t_parse_context *ctx, \
			int *i, int *j);
void		handle_redirectional(t_minishell *mini, t_parse_context *ctx, \
			int *i, int *j);
void		restore_default_signals(void);

//FUNCTION_ANALISE
int			first_token(t_minishell *mini);
void		exec_cmds(t_minishell *mini);

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

//ERROR
void		ft_error(char *error_msg, t_minishell *mini);
void		free_commands(t_cmd *commands);

//CD
int			custom_cd(t_minishell *mini);

//ENV
int			custom_env(t_minishell *mini);

//EXPORT
int			custom_export(t_minishell *mini);
//int		replace_value(t_env *found_env, char *value);

//UNSET
int			custom_unset(t_minishell *mini);

//KEY_UTILS
int			count_node(t_minishell *mini);
t_env		*find_key(t_minishell *mini, char *key);
int			check_valid_key(char *str);
int			replace_env_value(t_env *found_env, char *value);

//PWD
int			custom_pwd(t_minishell *mini);

//EXIT
int			custom_exit(t_minishell *mini);

//EXIT UTILS
bool		m_long(char *str);
int			is_num(char *str);
long long	ft_atoll(const char *str);

//PIPES
void		create_pipes(t_cmd *cmd);

#endif
