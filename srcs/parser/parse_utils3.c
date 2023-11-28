/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:44:10 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/28 15:35:41 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Ajoute la branche n + 1 apres la branche n */

void	ft_add_elem(t_shell *shell, t_elem *cur)
{
	t_elem	*tmp;

	if (!shell->tree->first)
	{
		cur->next = NULL;
		shell->tree->first = cur;
		return ;
	}
	tmp = shell->tree->first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cur;
	cur->prev = tmp;
	cur->next = NULL;
}

int	ft_size(char *input, int *i, int *start)
{
	int	quote;
	int	size;
	int	token;

	quote = 0;
	token = -1;
	size = 0;
	while (input[*i])
	{
		if (input[*i] == 34 || input[*i] == 39)
		{
			if (quote == input[*i])
				quote = 0;
			else if (quote == 0)
				quote = input[*i];
		}
		if (quote == 0 && ft_issyntax(input[*i]) == PIPE)
			break ;
		if (ft_istoken(input[*i]) && (quote == 0))
			token = ft_istoken(input[*i]);
		if (ft_isspace(input[*i]) && !ft_isspace(input[*i + 1])
			&& token != REDIR && quote == 0)
			size++;
		*i += 1;
	}
	return (ft_end_size(input, i, start, size, token));
}

char	*ft_return_avx(char *input, int *start, int size)
{
	char	*avx;
	int		i;

	size -= *start;
	avx = ft_calloc(sizeof(char), (size + 1));
	if (!avx)
		return (NULL);
	size += *start;
	i = 0;
	while (*start < size)
	{
		avx[i] = input[*start];
		i++;
		*start += 1;
	}
	avx[i] = '\0';
	return (avx);
}

char	*ft_write_current_av(char *input, int *start)
{
	int	quote;
	int	size;

	quote = 0;
	while (input[*start] == ' ')
		*start += 1;
	size = *start;
	while (input[size])
	{
		if (input[size] == 34 || input[size] == 39)
		{
			if (quote == input[size])
				quote = 0;
			else if (quote == 0)
				quote = input[size];
		}
		if (quote == 0 && (ft_isspace(input[size])
				|| ft_issyntax(input[size]) == REDIR
				|| ft_issyntax(input[size]) == PIPE))
			break ;
		size++;
	}
	return (ft_return_avx(input, start, size));
}

/* Ecrit la commande de la branche actuelle */
void	ft_write_cmd(t_elem *cur, char *input, int *start)
{
	int		end;
	int		i;
	t_red	*tmp;
	int		size;

	end = *start;
	i = *start;
	tmp = NULL;
	size = ft_size(input, &end, start);
	cur->av = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (!cur->av)
		return ;
	if (size == 0)
		cur->av = NULL;
	size = 0;
	while (i < end)
	{
		if (ft_isspace(input[i]))
			i++;
		else if (ft_issyntax(input[i]) == REDIR)
			tmp = ft_write_lst_redir(tmp, cur, input, &i);
		else
			cur->av[size++] = ft_write_current_av(input, &i);
	}
}
