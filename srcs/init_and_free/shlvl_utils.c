/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:26:06 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 01:21:16 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_isshlvl(char *cur_env)
{
	static char	*sh = "SHLVL";
	int			i;

	i = 0;
	while (sh[i])
	{
		if (cur_env[i] != sh[i])
			return (false);
		i++;
	}
	return (true);
}

void	ft_init_lvl(char *cur_env, int *lvl)
{
	int	i;

	i = 0;
	while (cur_env[i] != '=')
		i++;
	i++;
	*lvl = 0;
	while (cur_env[i])
	{
		*lvl = (*lvl * 10) + (cur_env[i] - '0');
		i++;
	}
	*lvl += 1;
}

char	*ft_convert_lvl(int lvl)
{
	char	*strlvl;
	int		len;

	len = ft_nbrlen(lvl);
	strlvl = ft_calloc(sizeof(char), (len + 1));
	if (!strlvl)
		return (NULL);
	strlvl[len--] = '\0';
	if (lvl == 0)
	{
		strlvl[0] = '0';
		return (strlvl);
	}
	while (lvl)
	{
		strlvl[len--] = (lvl % 10) + '0';
		lvl /= 10;
	}
	return (strlvl);
}

char	*ft_write_shlvl(char *cur_env)
{
	char	*new;
	char	*strlvl;
	int		lvl;
	int		i;

	ft_init_lvl(cur_env, &lvl);
	strlvl = ft_convert_lvl(lvl);
	new = ft_calloc(sizeof(char), 7 + ft_strlen(strlvl));
	if (!new)
		return (NULL);
	lvl = 0;
	while (cur_env[lvl] != '=')
	{
		new[lvl] = cur_env[lvl];
		lvl++;
	}
	new[lvl++] = '=';
	i = 0;
	while (strlvl[i])
		new[lvl++] = strlvl[i++];
	new[lvl] = '\0';
	free(strlvl);
	return (new);
}
