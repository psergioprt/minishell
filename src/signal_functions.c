/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:31:10 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/05 07:53:29 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_default_signals(void)
{
	struct sigaction	sa_default;

	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sa_default.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}

/*void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}*/

/*void	sigint_handler(int sig)
{
	t_minishell	*mini;

	(void)sig;
	if (g_in_prompt)
	{
		mini = (t_minishell *)g_in_prompt;
		mini->exit_status = 130;
	}
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	if (g_in_prompt)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}*/

void sigint_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
    g_exit_code = 130;  // Set g_in_prompt to SIGINT when the signal occurs
    rl_on_new_line();
    rl_replace_line("", 0);
    write(STDOUT_FILENO, "\n", 1);
    rl_redisplay();
}

void	init_sigaction(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
