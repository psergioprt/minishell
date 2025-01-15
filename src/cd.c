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
	new_env->value = ft_strdup(value);
	new_env->print = true;
	while (envvars->next)
		envvars = envvars->next;
	envvars->next = new_env;
	new_env->next = NULL;
}

void	has_found_env(t_env *found_env, char *key, char *dir)
{
	char    *new_value;

	new_value = ft_strjoin(key, dir);
	if (!new_value)
	{
		printf("malloc error\n");
		return ;
	}
	replace_value(found_env, new_value);
	free(new_value);
}

int update_pwd(t_minishell *mini, char *last_dir)
{
	char    *current_dir;
	char    cwd[1024];
	t_env   *found_env;

	current_dir = getcwd(cwd, sizeof(cwd));
	if (!current_dir)
	{
		printf("getcwd error\n");
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

int custom_cd(t_minishell *mini)
{
	char	*path;
	t_node	*node;
	char 	*last_dir;
	char	cwd[1024];
	//TODO: como no subject diz so absolute ou relative path, so fazer esses
	//TODO: trocar coiso que esta a espera de input para dizer o cwd? (Current Working Directory)
	//TODO: ja recebe as env vars expandidas certo?

	node = mini->tokenlst;
	last_dir = getcwd(cwd, sizeof(cwd));
	printf("last_dir: %s\n", last_dir);
	if (!node->next)
	{
		ft_error("cd: missing argument", mini);
		return (-1);
	}
	node = node->next; //Supostamente estara aqui o path
	if (node->next)
	{
		ft_error("cd: too many arguments", mini);
		return (-1);
	}
	path = node->token;
	if (chdir(path) == -1)
	{
		printf("cd error\n");
		return (-1);
	}
	update_pwd(mini, last_dir);
	return (1);
}
