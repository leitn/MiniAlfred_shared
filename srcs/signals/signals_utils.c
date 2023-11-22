/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:04:05 by hedubois          #+#    #+#             */
/*   Updated: 2023/10/25 02:44:17 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Ignore ctrl-z et ctrl-/,
redirige ctrl-c. ctrl-d est gere
par readline directement. */

void	ft_signals(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_ctrlc);
}

void	ft_ctrlc(int sig)
{
	extern int	g_error;

	(void)sig;
	g_error = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}
