/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_inhd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:30:02 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/24 18:49:38 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_signals_inhd(void)
{
	signal(SIGINT, &ft_ctrlc_inhd);
	signal(SIGQUIT, &ft_ctrlbs_inhd);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_ctrlc_inhd(int sig)
{
	t_shell	*shell;
	t_elem  *cur;
	extern int	g_error;

	(void)sig;
	shell = ft_getshell(NULL, 0);
	cur = shell->tree->first;
	g_error = 130;

}

void	ft_ctrlbs_inhd(int sig)
{
	extern int	g_error;

	(void)sig;
	g_error = 130;
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
