#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../Libft/libft.h"

typedef struct s_node
{
	char	*command;
	struct s_node *next;
}t_node;

t_node *create_command_node(const char *command);
void	add_command_node(t_node **head, const char *command);
void	free_list(t_node *head);
void	split_and_add_commands(t_node **head, const char *input);

#endif
