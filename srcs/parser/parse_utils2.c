/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:42:41 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/28 23:58:52 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* depend de ft_error_pipe (norme)
regarde si elle trouve des mots
avt le pipe trouve par elle,
renvoie false si oui, true sinon */

bool	ft_while_before(char *to_parse, int j, int i)
{
	int	tmp;

	tmp = j;
	while (j < i)
	{
		if (!ft_isspace(to_parse[j]) && !ft_issyntax(to_parse[j]))
			return (false);
		j++;
	}
	if (tmp == 0 && (to_parse[i] == '<' || to_parse[i] == '>'))
		return (false);
	return (true);
}
/* depend de ft_error_pipe (norme)
regarde si elle trouve des mots
apres le pipe trouve par elle,
renvoie false si oui, true sinon */

bool	ft_while_after(char *to_parse, int *i)
{
	if ((to_parse[*i] == '<' || to_parse[*i] == '>')
		&& (to_parse[*i] == to_parse[*i - 1]))
		*i += 1;
	if (to_parse[*i] == to_parse[*i - 1])
		return (true);
	while (to_parse[*i] && (to_parse[*i] != '|' || to_parse[*i] != '<'
			|| to_parse[*i] != '>'))
	{
		if (!ft_isspace(to_parse[*i]) && !ft_issyntax(to_parse[*i]))
			return (false);
		*i += 1;
	}
	return (true);
}

/* s'assure qu'il n'y a pas de double pipe,
de triple redir, et qu'il y a bien qqch avant
et apres chaque pipe et chaque redir */

bool	ft_error_pipe_or_redir(char *to_parse)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (to_parse[i])
	{
		if (to_parse[i] == '|' || to_parse[i] == '<' || to_parse[i] == '>')
		{
			j = k;
			if (ft_while_before(to_parse, j, i))
				return (true);
			k = ++i;
			if (ft_while_after(to_parse, &i))
				return (true);
		}
		i++;
	}
	return (false);
}
/* s'assure qu'il n'y ai pas d'unclosed quote,
renvoie true si c'est le cas */

bool	ft_unclosedquotes(char *to_parse)
{
	char	target;
	int		i;

	i = 0;
	while (to_parse[i])
	{
		if (to_parse[i] == 34 || to_parse[i] == 39)
		{
			target = to_parse[i];
			i++;
			if (!to_parse[i])
				return (true);
			while (to_parse[i] != target)
			{
				i++;
				if (!to_parse[i])
					return (true);
			}
		}
		i++;
	}
	return (false);
}
/* s'assure que la string contienne
autre chose que des espaces */

bool	ft_isempty(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]) && input[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}
