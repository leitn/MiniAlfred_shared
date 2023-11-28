/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diverses_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:26:48 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/28 15:54:55 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

/* return dans quelle cas de redir
se trouve la commande actuelle */

t_syntax	ft_returnredir(char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*i += 2;
			return (DOUBLEREDIRLEFT);
		}
		*i += 1;
		return (SIMPLEREDIRLEFT);
	}
	if (input[*i + 1] == '>')
	{
		*i += 2;
		return (DOUBLEREDIRRIGHT);
	}
	*i += 1;
	return (SIMPLEREDIRRIGHT);
}

int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

bool	ft_ishell(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
			return (true);
		i++;
	}
	return (false);
}
