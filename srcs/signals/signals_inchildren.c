/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_inchildren.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:40:42 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/24 14:58:08 by hedubois         ###   ########.fr       */
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
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (131);
	}
	if (sig == SIGINT)
		return (130);
	return (sig);
}

void	ft_check_return(int error_status)
{
	if (WIFEXITED(error_status))
		g_error = WEXITSTATUS(error_status);
	else if (WIFSIGNALED(error_status))
		g_error = ft_signal_return_handler(error_status);
}
