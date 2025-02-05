/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <pauldos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:23:41 by pauldos-          #+#    #+#             */
/*   Updated: 2025/02/05 07:54:27 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void 	handle_ctrl_c_hd(t_minishell *mini)
{
	(void)mini;
}

void	handle_heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_exit_code = SIGINT;
		close(STDIN_FILENO);
	}
}

void	set_signals_to_here_doc(void)
{
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, SIG_DFL);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
    	return (joined);
}

int	check_malloc(void *ptr)
{
	if (!ptr)
	{
		perror("malloc failed");
		return (1);
	}
	return (0);
}

void	init_heredoc(t_minishell *mini)
{
	mini->heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (check_malloc(mini->heredoc))
		return;
	mini->heredoc->index = 0;
	mini->heredoc->count_hd = 0;
	mini->heredoc->fd_heredoc_path = NULL;
	mini->heredoc->eof = NULL;
	mini->heredoc->eof_quote = false;
	mini->heredoc->next = NULL;
}

void	clear_heredoc_list(t_minishell *mini)
{
	t_heredoc *tmp_hd;
	while (mini->heredoc)
	{
		tmp_hd = mini->heredoc;
		mini->heredoc = mini->heredoc->next;
		if (tmp_hd->fd_heredoc_path)
			free(tmp_hd->fd_heredoc_path);
		if (tmp_hd->eof)
			free(tmp_hd->eof);
		free(tmp_hd);
	}
	mini->heredoc = NULL;
}

void	include_hd_path(t_minishell *mini)
{
	t_node	*tmp_token = mini->tokenlst;
	t_heredoc	*tmp_hd = mini->heredoc;
	
	while (tmp_token)
	{
		if (tmp_token->type == HEREDOC)
		{
			tmp_token->type = INPUT;
			tmp_token->target = tmp_hd->fd_heredoc_path;
			tmp_hd = tmp_hd->next;
		}
		tmp_token = tmp_token->next;
	}
}

int	find_next_env(char *line)
{
	int	i = 0;

	while (line[i])
	{
		if (line[i] == '$')
		return (i);
		i++;
	}
	return (-1);
}

char	*append_expanded_env(t_minishell *mini, char *result, char **pline, int pos)
{
	char	*before;
	int	j;
	char	*varToken;
	char	*expanded;
	char 	*rest;
	
	before = ft_substr(*pline, 0, pos);
	result = ft_strjoin_free(result, before);
	free(before);
	j = pos + 1;
	while ((*pline)[j] && (ft_isalnum((*pline)[j]) || (*pline)[j] == '_'))
        	j++;
	varToken = ft_substr(*pline, pos, j - pos);
	expanded = expand_env_var(varToken, mini);
	free(varToken);
	result = ft_strjoin_free(result, expanded);
	free(expanded);
	rest = ft_strdup(*pline + j);
	free(*pline);
	*pline = rest;
	return (result);
}


/*char	*append_expanded_env(t_minishell *mini, char *result, char **pline, int pos)
{
	char	*before = ft_substr(*pline, 0, pos);

	result = ft_strjoin_free(result, before);
	free(before);
	int	j = pos + 1;
	while ((*pline)[j] && (ft_isalnum((*pline)[j]) || (*pline)[j] == '_'))
        	j++;
	char	*varToken = ft_substr(*pline, pos, j - pos);
	char	*expanded = expand_env_var(varToken, mini);
	free(varToken);
	result = ft_strjoin_free(result, expanded);
	free(expanded);
	char *rest = ft_strdup(*pline + j);
	free(*pline);
	*pline = rest;
	return (result);
}*/

char 	*expand_env_vars_in_line(t_minishell *mini, char *line)
{
	char	*result = ft_strdup("");

	if (!result)
		return (NULL);
	int pos;
	while ((pos = find_next_env(line)) != -1)
	{
		result = append_expanded_env(mini, result, &line, pos);
	}
	result = ft_strjoin_free(result, line);
	free(line);
	return (result);
}

void	check_hd_expand(char **line, t_minishell *mini)
{
	char	*new_line = expand_env_vars_in_line(mini, *line);
	*line = new_line;
}

void	save_heredoc_info(t_minishell *mini)
{
	t_node	*tmp = mini->tokenlst;
	t_heredoc	*tmp_hd = NULL;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next)
		{
			if (!mini->heredoc)
			{
				mini->heredoc = malloc(sizeof(t_heredoc));
				if (check_malloc(mini->heredoc))
					return ;
				mini->heredoc->index = 1;
				mini->heredoc->eof = ft_strdup(tmp->next->token);
				mini->heredoc->eof_quote = false;
				mini->heredoc->fd_heredoc_path = NULL;
				mini->heredoc->count_hd = 0;
				mini->heredoc->next = NULL;
				if (!mini->heredoc->eof)
					fprintf(stderr, "Error: HEREDOC delimiter is NULL\n");
			}
			else
			{
				if (!mini->heredoc->eof)
				{
					mini->heredoc->eof = ft_strdup(tmp->next->token);
					if (!mini->heredoc->eof)
						fprintf(stderr, "Error: HEREDOC delimiter is NULL\n");
				}
				else
				{
					tmp_hd = mini->heredoc;
					while (tmp_hd->next)
						tmp_hd = tmp_hd->next;
					tmp_hd->next = malloc(sizeof(t_heredoc));
					if (check_malloc(tmp_hd->next))
						return ;
					tmp_hd = tmp_hd->next;
					tmp_hd->index = mini->heredoc->index + 1;
					tmp_hd->eof = ft_strdup(tmp->next->token);
					tmp_hd->eof_quote = false;
					tmp_hd->fd_heredoc_path = NULL;
					tmp_hd->count_hd = mini->heredoc->count_hd;
					tmp_hd->next = NULL;
					if (!tmp_hd->eof)
						fprintf(stderr, "Error: HEREDOC delimiter is NULL\n");
				}
			}
		}
		tmp = tmp->next;
	}
}

int	fill_fd_heredoc(t_heredoc *tmp_hd, t_minishell *mini)
{
	char	*line;

	tmp_hd->fd_heredoc = open(tmp_hd->fd_heredoc_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_hd->fd_heredoc == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			return (0);
		}
		if (ft_strcmp(line, tmp_hd->eof) == 0)
		{
			free(line);
			break ;
		}
		if (!tmp_hd->eof_quote)
			check_hd_expand(&line, mini);
		if (write(tmp_hd->fd_heredoc, line, ft_strlen(line)) == -1 || write(tmp_hd->fd_heredoc, "\n", 1) == -1)
            		perror("Error writing heredoc line");
		free (line);
	}
	if (close(tmp_hd->fd_heredoc) == -1)
		perror("Failed to close heredoc file");
	return (0);
}

void	handle_heredoc_child(t_heredoc *tmp_hd, t_minishell *mini)
{
	int status;

	set_signals_to_here_doc();
	status = fill_fd_heredoc(tmp_hd, mini);
	if (status == -1)
		perror("Error handling heredoc");
	exit (0);
}

void	heredoc(t_minishell *mini)
{
	t_heredoc	*tmp_hd;
	char		*num;
	int		status;
	pid_t		pid;
	
	save_heredoc_info(mini);
	if (mini->heredoc && mini->heredoc->eof == NULL)
		tmp_hd = mini->heredoc->next;
	else
		tmp_hd = mini->heredoc;
	while (tmp_hd)
	{
		num = ft_itoa(tmp_hd->index);
		tmp_hd->fd_heredoc_path = ft_strjoin("/tmp/tmp_heredoc", num);
		free(num);
		pid = fork();
		if (pid == 0)
			handle_heredoc_child(tmp_hd, mini);
	//	if (tmp_hd->fd_heredoc_path != NULL)
         //       		tmp_hd->fd_heredoc_path = NULL;
           // 	exit(0);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			handle_ctrl_c_hd(mini);
			return ;
		}
		tmp_hd = tmp_hd->next;
	}
	include_hd_path(mini);
}
