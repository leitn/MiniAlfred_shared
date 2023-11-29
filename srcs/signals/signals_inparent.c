/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_inparent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:04:05 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 17:51:36 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Ignore ctrl-z et ctrl-/,
redirige ctrl-c. ctrl-d est gere
par readline directement. */

t_shell	*ft_getshell(t_shell *shell, int trigger)
{
	static t_shell	*saved_shell;

	if (trigger == 1)
	{
		saved_shell = shell;
		return (NULL);
	}
	return (saved_shell);
}

void	ft_signals_inparent(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_ctrlc_inparent);
}

void	ft_ctrlc_inparent(int sig)
{
	t_shell	*shell;

	(void)sig;
	shell = ft_getshell(NULL, 0);
	shell->error_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}
