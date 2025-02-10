/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:31:10 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/09 23:24:27 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_default_signals(void) //Function kept
{
	struct sigaction	sa_default;

	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sa_default.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}

void	sigint_handler(int sig) //Function kept
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_code = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	sigint_handler_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_code = 130;
}

void	init_sigaction(int interactive)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	if (interactive)
		sa_int.sa_handler = sigint_handler;
	else
		sa_int.sa_handler = sigint_handler_child;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
