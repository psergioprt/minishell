#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_env_node
{
	char	*command;
	struct s_env_node *next;
}t_env_node;

t_env_node *create_command_node(const char *command);

#endif
