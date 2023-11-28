/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:53:27 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/28 15:59:42 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_env(t_elem *cur, t_syntax FLAG)
{
	static char	*err = "'\nthis implementation does not accept arg or option\n";

	if (FLAG == NO)
	{
		ft_putstr_fd("env: extra operand '", 2);
		ft_putstr_fd(cur->av[1], 2);
		ft_putstr_fd(err, 2);
	}

	else if (FLAG == OPTION)
	{
		ft_putstr_fd("env: invalid -- option '", 2);
		ft_putstr_fd(cur->av[1], 2);
		ft_putstr_fd(err, 2);
	}
}

void	ft_env(t_shell *shell, t_elem *cur, int pid)
{
	int	i;

	if (cur->av[1] && (ft_issyntax(cur->av[1][0]) == NO
		|| ft_issyntax(cur->av[1][0]) == OPTION))
	{
		ft_error_env(cur, ft_issyntax(cur->av[1][0]));
		return ;
	}
	i = 0;
	while (shell->env->envp[i])
	{
		if (cur->fd_wr > 0 && (pid != 0))
		{
			ft_putstr_fd(shell->env->envp[i++], cur->fd_wr);
			ft_putchar_fd('\n', cur->fd_wr);
		}
		else if ((pid == 0) || (cur->fd_wr == -2))
		{
			ft_putstr_fd(shell->env->envp[i++], 1);
			ft_putchar_fd('\n', 1);
		}
	}
	if (pid == 0)
		exit(0);
}
