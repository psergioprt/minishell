/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:02 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/16 14:52:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//cat test.txt | grep "apple" | wc -l
//2 pipes, 3 comandos

/* int	checking_pipes(t_minishell *mini)
{
	t_node	nodelst;

	nodelst = mini->tokenlst;
	//Fazer ciclo de enquanto tiver pipes
	//O primeiro manda o output
	//Os do meio redirecionam o input do anterior e o output do proximo
	//O ultimo redireciona o input do anterior
}
 */