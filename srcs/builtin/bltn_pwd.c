/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:26:17 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/06 14:55:28 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_pwd(t_shell *shell, t_elem *cur, int pid)
{
	char		*pwd;
	extern int	g_error;

	if (cur->av[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		g_error = 2;
		shell->exec_current = cur->next;
		return (false);
	}
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, cur->fd_wr);
	ft_putchar_fd('\n', cur->fd_wr);
	ft_add_to_the_bin(pwd, STR, shell->bin);
	shell->exec_current = cur->next;
	if (pid == 0)
		exit(0);
	return (true);
}
