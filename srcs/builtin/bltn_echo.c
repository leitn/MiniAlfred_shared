/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:39:51 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 22:27:03 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print(t_shell *shell, t_elem *cur, int i, bool no_ligne, int pid)
{
	if (cur->fd_wr > 0 && (pid != 0))
	{
		while (cur->av[i])
		{
			ft_putstr_fd(cur->av[i++], cur->fd_wr);
			if (cur->av[i])
				ft_putstr_fd(" ", cur->fd_wr);
		}
	}
	else if ((pid == 0) || (cur->fd_wr == -2))
	{
		while (cur->av[i])
		{
			ft_putstr_fd(cur->av[i++], 1);
			if (cur->av[i])
				ft_putstr_fd(" ", 1);
		}
	}
	if (no_ligne == false && cur->fd_wr > 0)
		ft_putstr_fd("\n", cur->fd_wr);
	else if (no_ligne == false && cur->fd_wr < 0)
		ft_putstr_fd("\n", 1);
	shell->error_status = 0;
}

void	ft_parent_close_echo(t_elem *cur, t_shell *shell)
{
	t_elem	*tmp;

	tmp = cur;
	while (tmp)
	{
		if (tmp->fd_rd > 0)
			close(tmp->fd_rd);
		if (tmp->fd_wr > 1)
			close(tmp->fd_wr);
		tmp = tmp->next;
	}
	ft_free_hd(shell);
}

void	ft_echo(t_shell *shell, t_elem *cur, int pid)
{
	int		i;
	int		j;
	bool	no_ligne;

	no_ligne = false;
	i = 1;
	if (cur->av[1] && ft_issyntax(cur->av[1][0]) == OPTION)
	{
		while (cur->av[i] && ft_issyntax(cur->av[i][0]) == OPTION)
		{
			j = 1;
			while (cur->av[i][j] && cur->av[i][j] == 'n')
				j++;
			if (j == ft_strlen(cur->av[i]))
				no_ligne = true;
			else
				break ;
			i++;
		}
	}
	ft_print(shell, cur, i, no_ligne, pid);
	if (pid == 0)
		ft_exitbltn(shell, 0);
	ft_parent_close_echo(cur, shell);
}

void	ft_exitbltn(t_shell *shell, int status)
{
	ft_filter(shell, FCLEAN);
	exit(status);
}
