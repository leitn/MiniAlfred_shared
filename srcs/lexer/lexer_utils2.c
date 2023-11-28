/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:12:13 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/28 19:41:44 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lex_av(t_shell *shell, t_elem *tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp->av[i])
	{
		j = 0;
		while (tmp->av[i][j])
		{
			if (tmp->av[i][j] == 34 || tmp->av[i][j] == 39)
				ft_rewrite(shell, tmp, i, &j);
			else if (tmp->av[i][j] == '$')
				ft_rewrite_dollard(shell, tmp, i, &j);
			else
				j++;
			if (!tmp->av[i][j])
				break ;
		}
		i++;
	}
}

bool	ft_continue(char next, int *j)
{
	if (!next)
	{
		*j += 1;
		return (false);
	}
	if (next == ' ' || next == '.' || ft_issyntax(next)
		|| next == '%' || next == '$' || next == ':' || next == '=')
	{
		*j += 1;
		return (false);
	}
	return (true);
}
