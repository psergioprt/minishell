/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:08:38 by pauldos-          #+#    #+#             */
/*   Updated: 2024/12/28 01:07:16 by pauldos-         ###   ########.fr       */
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
	bool	has_pipe;
	char	*last_command_out;
}	t_minishell;

typedef struct s_parse_context
{
	char		*current_token;
	const char	*input;
	int			index;
	char		quote;
}	t_parse_context;

t_node	*create_command_node(const char *command);
void	add_command_node(t_minishell *mini, const char *command);
void	free_list(t_minishell *mini);
void	split_and_add_commands(t_minishell *mini, const char *input);
void	init_variables(t_minishell *mini, t_parse_context *ctx, \
		const char *input, char *current_token);
void	cleanup_readline(void);

#endif
