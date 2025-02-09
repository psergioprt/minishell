#include "../include/minishell.h"

int	g_exit_code;

//TODO isto e desnecessario com o comando exit
void	read_lines_exit(t_minishell *mini, char *read)
{
	if (read == NULL)
	{
		write(STDOUT_FILENO, "\033[1G\033[2kexit\0\n", 15);
		free_list(mini);
		//cleanup_fd(mini);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);//TODO PERGUNTAR SE DEVE TER ISTO (fecha 3 open 3(std))
		exit (0);
	}
}

bool	is_spaces(char *read)
{
	int	i;
	
	i = 0;
	while (read[i])
	{
		if (read[i] != ' ' && !(read[i] >= 9 && read[i] <= 13))
			return (true);
		i++;
	}
	return (false);
}

void	read_lines(t_minishell *mini)
{
	char	*read;

	read = NULL;
	while (1)
	{
		mini->interactive = 1;
		read = readline("\033[1;31mminishell>\033[0m ");
		if (g_exit_code != 0)
		{
			mini->exit_status = g_exit_code;
			g_exit_code = 0;
		}
		read_lines_exit(mini, read); //TODO da segfault quando comentada no cntrl D	
		if (*read && is_spaces(read))
		{
			split_and_add_commands(mini, read);
			add_history(read);
			if (mini->has_error)
			{
				free(read);
				free_list(mini);
				clear_heredoc_list(mini);
				continue ;
			}
			mini->interactive = 0;
			init_sigaction(mini->interactive);
			mini->saved_stdout = dup(STDOUT_FILENO);
			mini->saved_stdin = dup(STDIN_FILENO);
			exec_cmds(mini);
			redir_fds(mini->saved_stdout, STDOUT_FILENO);
			redir_fds(mini->saved_stdin, STDIN_FILENO);
			close(mini->saved_stdout);
			close(mini->saved_stdin);
			free_commands(mini->commands);
			free_list(mini);
			if (mini->heredoc->fd_heredoc_path)
				unlink(mini->heredoc->fd_heredoc_path); //Added to remove heredoc after use
			clear_heredoc_list(mini);
			mini->interactive = 1;
			init_sigaction(mini->interactive);
		}
		free(read);
	}
	free_commands(mini->commands);
	free_list(mini);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	mini;

	mini.interactive = 1;
	init_sigaction(mini.interactive);
	(void)argc;
	(void)argv;	
	if (argc != 1 || argv[1])
	{
		printf("Usage: ./minishell\nDoes not accept additional arguments.\n");
		exit (1);
	}
	mini.tokenlst = NULL;
	mini.exit_status = 0;
	mini.i = 0; //TODO checkar se e preciso
	parse_env(&mini, env);
	copy_env(env, &mini);
	read_lines(&mini);
	free_envvars(&mini);
	return (0);
}
