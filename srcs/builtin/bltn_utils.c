/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:29:18 by heduv                                    */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar_fd(str[i++], fd);
}

bool	ft_strcmp(char *cmd, char *cmp)
{
	int		i;

	i = 0;
	while (cmp[i])
	{
		if (cmd[i] != cmp[i])
			return (false);
		i++;
	}
	if (ft_strlen(cmd) == ft_strlen(cmp))
		return (true);
	return (false);
}

bool	ft_cmpbegin(char *cmd, char *cmp)
{
	int	i;

	i = 0;
	while (cmp[i])
	{
		if (cmd[i] != cmp[i])
			return (false);
		i++;
	}
	if (cmd[i] == '=')
		return (true);
	return (false);
}
