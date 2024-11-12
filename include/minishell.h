#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../Libft/libft.h"

typedef struct s_env_node
{
	char	*command;
	struct s_env_node *next;
}t_env_node;

t_env_node *create_command_node(const char *command);
void	add_command_node(t_env_node **head, const char *command);
void	free_list(t_env_node *head);

#endif
