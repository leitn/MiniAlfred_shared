/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_inhd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:30:02 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 23:52:39 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_signals_inhd(void)
{
	signal(SIGINT, &ft_ctrlc_inhd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_ctrlc_inhd(int sig)
{
	(void)sig;
	g_error = 130;
	close(STDIN_FILENO);
}

int	ft_ctrld_inhd(t_elem *cur, t_red *red, int save)
{
	t_elem	*tmp;

	tmp = cur;
	if (tmp->fd_rd > 2)
		close(tmp->fd_rd);
	close(save);
	ft_putstr_fd("MiniAlfred: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(red->av, 2);
	ft_putstr_fd("')\n", 2);
	return (-42);
}
