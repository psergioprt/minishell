/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:55:09 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/07 18:55:09 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO isto aqui tudo

void	ft_error(char *error_msg, t_minishell *mini)
{
	printf("%s\n", error_msg);
	ft_isalnum(mini->tokenlst->token[1]); //TODO apagar
	//free_list(mini); //TODO TALVEZ NAO FAZER FREE SE FOR PARA USAR SEMPRE QUE DA ERRO NUM COMANDO
	//TODO vai ter de sair do processo filho e voltar para o pai
}

static void free_tokens(t_node *tokens)
{
	t_node *tmp;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->token);
		free(tmp);
	}
}

void free_commands(t_cmd *commands)
{
	t_cmd *tmp;
	while (commands)
	{
		tmp = commands;
		commands = commands->next;
		free_tokens(tmp->tokens);
		free(tmp);
	}
}
