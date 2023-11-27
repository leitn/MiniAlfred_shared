/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:09:04 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/27 18:08:17 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// verifie si le dernier redir est un outfile
bool	ft_check_outfile(t_elem *cur)
{
	t_red	*tmp;

	tmp = cur->redirs;
	if (tmp == NULL)
		return(false);
	while (tmp)
	{
		if (tmp->syn == SIMPLEREDIRRIGHT || tmp->syn == DOUBLEREDIRRIGHT)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	ft_builtin_fds(t_elem *cur)
{
	if (cur->av)
	{
		if (ft_strcmp(cur->av[0], "exit") || ft_strcmp(cur->av[0], "cd"))
		{
			cur->fd_rd = 0;
			cur->fd_wr = 1;
		}
		else if (ft_strcmp(cur->av[0], "export") || ft_strcmp(cur->av[0], "unset"))
		{
			cur->fd_rd = 0;
			cur->fd_wr = 1;
		}
	}
}

bool	ft_complex_fds(t_shell *shell)
{
	t_red	*tmpr;
	t_elem	*tmpe;
	int		i;

	tmpe = shell->tree->first;
	i = 0;
	while(tmpe)
	{
		i++;
		// if (tmp->av)
		// 	printf("\n Passage %i\ntmp->av[0] == %s\ntmp->path  == %s", i, tmp->av[0], tmp->path);
		tmpr = tmpe->redirs;
		while(tmpr)
		{
			// printf ("\nBOUCLE REDIRS\n");
			if (tmpr->syn == SIMPLEREDIRRIGHT && !ft_simpledirright(tmpe, tmpr))
				return (false);
			if (tmpr->syn == DOUBLEREDIRRIGHT && !ft_doubledirright(tmpe, tmpr))
				return (false);
			if (tmpr->syn == SIMPLEREDIRLEFT && !ft_simpleleftdir(tmpe, tmpr))
				return(false);
			if (tmpr->syn == DOUBLEREDIRLEFT && !ft_doubledirleft(shell, tmpe, tmpr))
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
	// printf("\n\n------------------------------\n\n");
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

