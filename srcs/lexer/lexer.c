/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:57:39 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/23 16:18:31 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Return la string trouve a partir du dollard,
pour appeler getenv(). */
char	*ft_returnenv(char *cmd, int index)
{
	char	*getenvp;
	int		i;

	i = index + 1;
	while (cmd[i] && (cmd[i] != ' ' || cmd[i] != '"'
			|| cmd[i] == 34 || cmd[i] == '$'))
		i++;
	i -= (index + 1);
	getenvp = ft_calloc(sizeof(char), i + 1);
	if (!getenvp)
		return (NULL);
	i = 0;
	index++;
	while (cmd[index] && !ft_isspace(cmd[index]) && !ft_issyntax(cmd[index]))
	{
		if (cmd[index] == 34 || cmd[index] == 39 || cmd[index] == '$')
			break ;
		getenvp[i] = cmd[index];
		i++;
		index++;
	}
	getenvp[i] = '\0';
	return (getenvp);
}

void	ft_remove_quotes(t_elem *cur, int index, int start, int *end)
{
	char	*new;
	char	target;
	int		i;
	int		j;

	new = ft_calloc(sizeof(char), (ft_strlen(cur->av[index])));
	if (!new)
		return ;
	i = 0;
	j = 0;
	target = 0;
	while (cur->av[index][i])
	{
		if (i == start)
			target = cur->av[index][i++];
		else if (target != 42 && cur->av[index][i] == target)
		{
			target = 42;
			*end = i++;
		}
		else
			new[j++] = cur->av[index][i++];
	}
	new[j] = '\0';
	free(cur->av[index]);
	cur->av[index] = new;
}

void	ft_rewrite(t_shell *shell, t_elem *cur, int	index, int *jindex)
{
	char	target;
	int		end;

	target = cur->av[index][*jindex];
	end = *jindex;
	end++;
	while (cur->av[index][end] && cur->av[index][end] != target)
	{
		if (cur->av[index][end] == '$' && target == 34)
			ft_rewrite_dollard(shell, cur, index, &end);
		end++;
	}
	ft_remove_quotes(cur, index, *jindex, &end);
	*jindex = end - 1;
}

/* Parcours toute les commandes dans toutes
les branches a la recherche d'un dollard, en
dehors de simples quotes. Si elle en trouve,
les remplace par la variable correspondantes. */

void	ft_lex(t_shell *shell)
{
	t_elem	*tmp;

	tmp = shell->tree->first;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->av)
			ft_lex_av(shell, tmp);
		tmp = tmp->next;
	}
}
