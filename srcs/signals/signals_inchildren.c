/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_inchildren.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:40:42 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 23:52:14 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_signals_inchildren(void)
{
	signal(SIGINT, &ft_ctrlc_inchildren);
	signal(SIGQUIT, &ft_ctrlbs_inchildren);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_ctrlc_inchildren(int sig)
{
	(void)sig;
	g_error = 130;
}

void	ft_ctrlbs_inchildren(int sig)
{
	(void)sig;
	g_error = 131;
}

int	ft_signal_return_handler(int sig)
{
	if (sig + 128 == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (sig + 128 == 130)
		ft_putchar_fd('\n', 2);
	return (sig + 128);
}

void	ft_recast_return(t_shell *shell)
{
	if (g_error != 0)
	{
		shell->error_status = g_error;
		g_error = 0;
	}
	if (WIFEXITED(shell->error_status))
		shell->error_status = WEXITSTATUS(shell->error_status);
	else if (WIFSIGNALED(shell->error_status))
		shell->error_status
			= ft_signal_return_handler(WTERMSIG(shell->error_status));
	if (shell->error_status == 255)
		shell->error_status = 127;
}
