/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:35:07 by jcavadas          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:06 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(t_node *data)
{
	int		i;
	char	*pathname;
	char	**paths;
	
	i = 0;
	while (ft_strncmp(data->envvars[i].key, "PATH", 4) != 0)
		i++,
	paths = ft_split(data->envvars[i].value, ':');
	i = 0;
	while (paths[i++])
	{
		pathname = ft_strjoin(paths[i], '/' + data->command); //TODO fazer join com o comando tambem ex:ls
		if (access(pathname, F_OK) == 0)
			return (pathname);
	}
	return ("error");
}

int	execute_execve(t_node *data)
{
	//TODO: fazer a cena de antes de fazer o execve
	// dar split no $PATH nos ':'
	char	*pathname;
	char	**argv;
	int		len;
	int		i;
	
	i = 0;
	len = ft_strlen(data->token);
	printf("ERROR\n");	
	ft_strlcpy(data->command, data->token, len);
	printf("ERROR2\n"); //TODO: esta a seg faultar aqui	
	//TODO: transformar todos os tokens/argumentos da funcao num array argv[]

	printf("data->command: %s\n", data->command);
	
	while (data->next)
		i++;
	argv = (char **)malloc(sizeof(char *) * i);
	if (!argv)
		return(-1);
	while (data->next)
	{
		len = ft_strlen(data->token);
		ft_strlcpy(argv[i++], data->token, len);
		data = data->next;
	}
	argv[i] = '\0';
	//TODO: apagar testes argv
	i = 0;
	while (argv[i++])
		printf("Argv[%d]: %s\n", i, argv[i]);
	//TODO: apagar testes argv



	//TODO: testar se esta a ficar todos os argumentos em argv para o execve
	pathname = find_path(data);
	
	printf("Pathname: %s\n", pathname); //TODO: Apagar teste find_path

	//TODO: testar find_path
	return (1);
}
