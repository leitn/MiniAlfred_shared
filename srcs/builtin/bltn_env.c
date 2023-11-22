/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:53:27 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/06 14:54:55 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_shell *shell, t_elem *cur, int pid)
{
	int		i;
	static char	*err = "'\nthis implementation does not accept arg or option";

	i = 0;
	if (cur->av[1] && ft_issyntax(cur->av[1][0]) == NO)
	{
		ft_putstr_fd("env: extra operand '", 2);
		ft_putstr_fd(cur->av[1], 2);
		ft_putstr_fd(err, 2);
		return ;
	}
	if (cur->av[1] && ft_issyntax(cur->av[1][0]) == OPTION)
	{
		ft_putstr_fd("env: invalid -- option '", 2);
		ft_putstr_fd(cur->av[1], 2);
		ft_putstr_fd(err, 2);
		return ;
	}
	while (shell->env->envp[i])
	{
		ft_putstr_fd(shell->env->envp[i++], cur->fd_wr);
		ft_putchar_fd('\n', cur->fd_wr);
	}
	if (pid == 0)
		exit(0);
}
