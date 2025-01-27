/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:31:02 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/27 14:31:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int handle_direct_path(t_minishell *mini, char **argv)
{
	int error_code = execpath_error(mini->command);
	if (error_code != 0)
	{
		mini->exit_status = error_code;
		free(mini->command);
		int j = 0;
		while (argv[j])
			free(argv[j++]);
		free(argv);
		return (-1);
	}
	return (0);
}
