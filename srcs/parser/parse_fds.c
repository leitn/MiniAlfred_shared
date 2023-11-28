/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:09:04 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/28 23:43:39 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// verifie si le dernier redir est un outfile
bool	ft_check_outfile(t_elem *cur)
{
	t_red	*tmp;

	tmp = cur->redirs;
	if (tmp == NULL)
		return (false);
	while (tmp)
	{
		if (tmp->syn == SIMPLEREDIRRIGHT || tmp->syn == DOUBLEREDIRRIGHT)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	ft_builtin_fds(t_elem *cur)
{
	if (cur->av && cur->av[0])
	{
		if (ft_strcmp(cur->av[0], "exit") || ft_strcmp(cur->av[0], "cd"))
		{
			cur->fd_rd = 0;
			cur->fd_wr = 1;
			return (true);
		}
		else if (ft_strcmp(cur->av[0], "export")
			|| ft_strcmp(cur->av[0], "unset"))
		{
			cur->fd_rd = 0;
			cur->fd_wr = 1;
			return (true);
		}
	}
	return (false);
}

bool	ft_complex_fds(t_shell *shell)
{
	t_red	*tmpr;
	t_elem	*tmpe;
	int		i;

	tmpe = shell->tree->first;
	i = 0;
	while (tmpe)
	{
		i++;
		tmpr = tmpe->redirs;
		while (tmpr)
		{
			if (tmpr->syn == SIMPLEREDIRRIGHT
				&& !ft_simpledirright(tmpe, tmpr, shell))
				return (false);
			if (tmpr->syn == DOUBLEREDIRRIGHT
				&& !ft_doubledirright(tmpe, tmpr, shell))
				return (false);
			if (tmpr->syn == SIMPLEREDIRLEFT
				&& !ft_simpleleftdir(tmpe, tmpr, shell))
				return (false);
			if (tmpr->syn == DOUBLEREDIRLEFT
				&& !ft_heredoc(shell, tmpe, tmpr))
				return (false);
			tmpr = tmpr->next;
		}
		if (i > 1)
			tmpe->fd_rd = -2;
		if (tmpe->next && ft_check_outfile(tmpe) == false)
			tmpe->fd_wr = -2;
		ft_builtin_fds(tmpe);
		tmpe = tmpe->next;
	}
	return (true);
}

bool	ft_manage_fds(t_shell *shell)
{
	t_elem	*tmp;

	tmp = shell->tree->first;
	while (tmp)
	{
		tmp->fd_rd = 0;
		tmp->fd_wr = 1;
		tmp = tmp->next;
	}
	return (ft_complex_fds(shell));
}

