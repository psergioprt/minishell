/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:06:43 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/09 12:06:43 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO : If you attempt to unset a variable that does not exist, unset does nothing and does not return an error.
//TODO: Se tiver mais que uma variavel da unset a todas 
//EX: unset VAR1 VAR2

void	delete_env(t_minishell *mini, t_env **envvars, t_env **prev_envvar)
{
	t_env *temp;
	
	temp = *envvars;
	if (*prev_envvar) // Not the first node
		(*prev_envvar)->next = (*envvars)->next;
	else // First node, update head of the list
		mini->envvars = (*envvars)->next;

	// Free the memory for the current node
	free(temp->key);
	free(temp->value);
	free(temp);
}

void run_varlst(t_minishell *mini, t_node *varlst)
{
	t_env		*envvars;
	t_env		*prev_envvar;
	int			var_len;

	while (varlst)
	{
		envvars = mini->envvars;
		prev_envvar = NULL;
		var_len = ft_strlen(varlst->token);
		while (envvars)
		{
			if (ft_strlen(envvars->key) == var_len && ft_strncmp(envvars->key, varlst->token, var_len) == 0)
			{
				delete_env(mini, &envvars, &prev_envvar);
				break;
			}
			prev_envvar = envvars;
			envvars = envvars->next;
		}
		varlst = varlst->next;
	}
}

int	custom_unset(t_minishell *mini)
{
	t_node		*varlst;

	varlst = mini->tokenlst;
	if (varlst->next)
		varlst = varlst->next;
	if (varlst->token && varlst->token[0] == '-' && varlst->token[1])
	{
		printf("unset: %s: invalid option\n", varlst->token);
		return (2);
	}
	else if (varlst->token && varlst->token[0] == '-' && !(varlst->token[1]))
		return (0);
	run_varlst(mini, varlst);
	return (0);
}
