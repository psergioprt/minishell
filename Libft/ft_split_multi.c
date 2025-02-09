/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:32 by jcavadas          #+#    #+#             */
/*   Updated: 2025/02/09 18:10:04 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_delim(char c, const char *delims)
{
	size_t	i;

	i = 0;
	while (delims[i])
	{
		if (c == delims[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_wordcount(char const *s, const char *delims)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && is_delim(s[i], delims))
			i++;
		if (s[i])
			words++;
		while (s[i] && !is_delim(s[i], delims))
			i++;
	}
	return (words);
}

static void	ft_freemalloc(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**ft_tudo(char const *s, char **tab, const char *delims, size_t j)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && is_delim(s[i], delims))
			i++;
		j = i;
		while (s[i] && !is_delim(s[i], delims))
			i++;
		if (i > j)
		{
			tab[k] = malloc(sizeof(char) * (i - j + 1));
			if (!tab[k])
			{
				ft_freemalloc(tab);
				return (NULL);
			}
			ft_strlcpy(tab[k++], &s[j], i - j + 1);
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split_multi(char const *s, const char *delims)
{
	char	**tab;
	size_t	j;

	j = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_wordcount(s, delims) + 1));
	if (!tab)
		return (NULL);
	tab = ft_tudo(s, tab, delims, j);
	return (tab);
}
