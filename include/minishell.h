#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../Libft/libft.h"

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	print; //Quando e so key, so imprime no export sem mais nada, se nao so imprime o que tiver pelo menos key=
}t_env;


typedef struct s_node
{
	char	*token; //Acho que fica mais certo que command porque nao e obrigatoriamente um command
	//struct s_node *prev; //E preciso??
	char	**envp; //so copia o que tem para usar no execve
	t_env	*envvars;
	struct s_node *next;
}t_node;

t_node	*create_command_node(const char *command);
void	add_command_node(t_node **head, const char *command);
void	free_list(t_node *head);
void	split_and_add_commands(t_node **head, const char *input);

void	first_token(t_node *data);

void	custom_echo(t_node *data);

#endif
