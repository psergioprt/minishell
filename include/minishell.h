/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:08:38 by pauldos-          #+#    #+#             */
/*   Updated: 2025/01/15 13:56:20 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>

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

typedef struct s_minishell
{
	char	*command;
	char	**envp;
	t_node	*tokelst;
	t_env	*envvars;
	int		has_pipe;
	bool	disable_expand;
	bool	has_error;
	char	*last_command_out;
	int		env_count;
	char	*prompt;
}	t_minishell;

typedef struct s_parse_context
{
	char		*current_token;
	const char	*input;
	int			index;
	char		quote;
	const char	*exit_status;
}	t_parse_context;

typedef struct s_token_context
{
	char			*current_token;
	int				*i;
	int				*j;
	t_parse_context	*ctx;
}	t_token_context;

t_node	*create_command_node(const char *command);
void	add_command_node(t_minishell *mini, const char *command);
void	free_list(t_minishell *mini);
void	split_and_add_commands(t_minishell *mini, const char *input);
void	init_variables(t_minishell *mini, t_parse_context *ctx, \
		const char *input, char *current_token);
void	cleanup_readline(void);
void	free_envvars(t_minishell *mini);
void	parse_env(t_minishell *mini, char *env[]);
char	*expand_env_var(char *token, t_minishell *mini);
void	copy_env(char *env[], t_minishell *mini);
char	*get_env_value(char *env_name, t_minishell *mini);
void	print_envvar(t_minishell *mini);
void	init_sigaction(void);
#endif
