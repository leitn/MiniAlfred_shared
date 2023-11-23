/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:47:27 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/23 15:34:46 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_is_a_builtin(char *isbltn)
{
	if(ft_strcmp(isbltn, "echo")
		|| ft_strcmp(isbltn, "cd")
		|| ft_strcmp(isbltn, "pwd")
		|| ft_strcmp(isbltn, "export")
		|| ft_strcmp(isbltn, "unset")
		|| ft_strcmp(isbltn, "env")
		|| ft_strcmp(isbltn, "exit"))
		return (true);
	return (false);
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	while(array[len])
		len++;
	return(len);
}

char	*ft_strcpy(char *src)
{
	char	*dst;
	int		i;

	dst = ft_calloc(sizeof(char), (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_joinpath(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*init_path(t_shell *shell, t_elem *cur)
{
	int		i;
	char	**cmd_path;

	i = 0;
	cmd_path = ft_calloc(ft_array_len(shell->env->paths), (sizeof(char *) + 1));
	if (!cmd_path)
		return (NULL);
	ft_add_to_the_bin(cmd_path, STRARR, shell->bin);
	while (shell->env->paths[i] != NULL)
	{
		cmd_path[i] = ft_joinpath(shell->env->paths[i], cur->av[0]);
		i++;
	}
	cmd_path[i] = NULL;
	i = 0;
	while (cmd_path[i])
	{
		if (access(cmd_path[i], F_OK | X_OK) == 0)
			return (ft_strcpy(cmd_path[i]));
		i++;
	}
	return (NULL);
}




