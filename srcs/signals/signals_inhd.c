/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_inhd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:30:02 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/27 14:28:32 by letnitan         ###   ########.fr       */
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
	t_shell	*shell;

	shell = ft_getshell(NULL, 1);
	(void)sig;
	g_error = 130;
	// close(STDIN_FILENO); TO FIX : test me :)
}

int	ft_ctrld_inhd(t_shell *shell, t_elem *cur, t_red *red)
{
	t_elem	*tmp;

	tmp = shell->tree->first;
	g_error = 0;
	tmp = cur;
	while (tmp)
	{
		if (tmp->fd_rd > 2)
			close(tmp->fd_rd);
		unlink(tmp->hd_name);
		tmp = tmp->next;
	}
	ft_putstr_fd("MiniAlfred: warning: here-document ",2);
	ft_putstr_fd("delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(red->av, 2);
	ft_putstr_fd("')\n", 2);
	return (-42);
}
