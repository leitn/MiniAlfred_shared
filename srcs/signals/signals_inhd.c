/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_inhd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:30:02 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/24 18:16:54 by letnitan         ###   ########.fr       */
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

	(void)sig;
	shell = ft_getshell(NULL, 0);
	cur = shell->tree->first;
	shell->ss = false;
	g_error = 130;
	while(cur)
	{
		if (cur->hd_name != NULL)
		{
			close(cur->fd_rd);
			unlink(cur->hd_name);
		}
		cur = cur->next;
	}
}

void	ft_ctrlbs_inhd(int sig)
{
	t_shell	*shell;
	t_elem  *cur;

	(void)sig;
	shell = ft_getshell(NULL, 0);
	cur = shell->tree->first;
	shell->ss = false;
	while(cur)
	{
		if (cur->hd_name != NULL)
		{
			if (cur->fd_rd > 2)
				close(cur->fd_rd);
			unlink(cur->hd_name);
		}
		cur = cur->next;
	}
	g_error = 130;
}
