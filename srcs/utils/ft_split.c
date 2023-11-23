/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:11:41 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/23 15:35:26 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_errorfree(char **split)
{
	char	**tmp;

	tmp = split;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(split);
}

static int	ft_count_strs(char const *s, char c)
{
	int	i;
	int	strs;

	i = 0;
	strs = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			strs++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (strs);
}

static int	ft_wordlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_write_word(char *s, char c, char **split)
{
	char	*wrd;
	int		i;
	int		wrdlen;

	i = 0;
	wrdlen = ft_wordlen(s, c);
	wrd = ft_calloc(sizeof(char), (wrdlen + 1));
	if (!wrd)
	{
		ft_errorfree(split);
		return (NULL);
	}
	while (s[i] && s[i] != c)
	{
		wrd[i] = s[i];
		i++;
	}
	wrd[i] = '\0';
	return (wrd);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		wdnb;
	int		i;
	char	*str;

	str = (char *)s;
	wdnb = ft_count_strs(str, c);
	split = ft_calloc(sizeof(char *), (wdnb + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == c)
			str++;
		if (*str != '\0')
		{
			split[i] = ft_write_word(str, c, split);
			i++;
		}
		while (*str != '\0' && *str != c)
			str++;
	}
	split[i] = 0;
	return (split);
}
