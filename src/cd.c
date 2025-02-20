/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:58:41 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/08 10:58:41 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//fazer update/criar env var de PWD e OLDPWD
void	add_env_variable(t_minishell *mini, char *key, char *value)
{
	t_env	*envvars;
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	envvars = mini->envvars;
	new_env->key = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	new_env->print = true;
	if (!envvars)
	{
		new_env->next = NULL;
		mini->envvars = new_env;
		return ;
	}
	while (envvars->next)
		envvars = envvars->next;
	envvars->next = new_env;
	new_env->next = NULL;
}

void	has_found_env(t_env *found_env, char *key, char *dir)
{
	char	*new_value;

	if (dir)
		new_value = ft_strjoin(key, dir);
	else
		new_value = ft_strdup(key);
	if (!new_value)
	{
		ft_putstr_fd("malloc error\n", 2);
		return ;
	}
	replace_env_value(found_env, new_value);
	free(new_value);
}

int	update_pwd(t_minishell *mini, char *last_dir)
{
	char	*current_dir;
	char	cwd[1024];
	t_env	*found_env;

	current_dir = getcwd(cwd, sizeof(cwd));
	if (!current_dir)
	{
		ft_putstr_fd("getcwd error\n", 2);
		return (-1);
	}
	found_env = find_key(mini, "OLDPWD");
	if (found_env != NULL)
		has_found_env(found_env, "OLDPWD=", last_dir);
	else
		add_env_variable(mini, "OLDPWD", last_dir);
	found_env = find_key(mini, "PWD");
	if (found_env != NULL)
		has_found_env(found_env, "PWD=", current_dir);
	else
		add_env_variable(mini, "PWD", current_dir);
	return (1);
}

int	check_cd_args(t_node **node)
{
	if (!(*node)->next)
	{
		ft_putstr_fd("cd: missing argument\n", 2);
		return (1);
	}
	(*node) = (*node)->next;
	if ((*node)->next)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	custom_cd(t_minishell *mini)
{
	char	*path;
	t_node	*node;
	char	*last_dir;
	char	cwd[1024];

	node = mini->commands->tokens;
	last_dir = getcwd(cwd, sizeof(cwd));
	if (check_cd_args(&node) == 1)
		return (1);
	path = node->token;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	update_pwd(mini, last_dir);
	return (0);
}
