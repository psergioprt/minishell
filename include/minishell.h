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
	char			*key;
	char			*value;
	bool			print; //Quando e so key, so imprime no export sem mais nada, se nao so imprime o que tiver pelo menos key= 1-PRINT, 2-NOT
	struct s_env	*next;
}t_env;

typedef struct s_node
{
	char			*token; //TODO: temos de mudar para a logica agora ir ver os tokens e adicionar nos tokens
	struct s_node	*next;	
}t_node;

typedef struct s_minishell 
{
	char			*command; //TODO: tem de criar uma estrutura nova que fica dentro de esta que guarda os tokens com a mesma logica
	char			**envp; //so copia o que tem para usar no execve
	t_node			*tokenlst;
	t_env			*envvars;
	bool			has_pipe; //TODO: Inicializar a falso
	char			*last_command_out; //TODO: fazer logica de se tem pipe nao imprimir e guardar aqui
}t_minishell;

typedef struct s_parse_context
{
	char		*current_token;
	const char	*input;
	char		quote;
	//int			index;
}	t_parse_context;


t_node	*create_command_node(const char *command);
void	add_command_node(t_minishell *mini, const char *command);
void	free_list(t_minishell *mini);
void	split_and_add_commands(t_minishell *mini, const char *input);

void	first_token(t_minishell *mini);

void	custom_echo(t_minishell *mini);

//Splits
void	parse_env(t_minishell *node, char *env[]);
void	copy_env(char *env[], t_minishell *mini);


//EXEC
int		execute_execve(t_minishell *mini);

#endif
