/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:53:40 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 18:01:11 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_simple_export(t_shell *shell, t_elem *cur, int pid)
{
	int	i;

	i = 0;
	if (!shell->env->envp)
	{
		if (pid == 0)
			exit(0);
		return (true);

	}
	while (shell->env->envp[i])
	{
		ft_putstr_fd("export ", cur->fd_wr);
		ft_putstr_fd(shell->env->envp[i++], cur->fd_wr);
		ft_putchar_fd('\n', cur->fd_wr);
	}
	if (pid == 0)
		exit (0);
	return (true);
}
