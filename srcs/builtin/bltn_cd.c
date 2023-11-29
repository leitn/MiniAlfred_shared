/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 03:47:57 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 18:35:50 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_chdir2(t_shell *shell)
{
	char		*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (false);
	ft_add_to_the_bin(new_pwd, STR, shell->bin);
	ft_update_var(shell->env, "PWD", new_pwd);
	return (true);
}

bool	ft_chdir(t_shell *shell, char *path, int pid)
{
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		if (pid == 0)
			ft_exitbltn(shell, 1);
		return (false);
	}
	ft_add_to_the_bin(old_pwd, STR, shell->bin);
	ft_update_var(shell->env, "OLDPWD", old_pwd);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: invalid path\n", 2);
		shell->error_status = 2;
		if (pid == 0)
			ft_exitbltn(shell, 2);
		return (false);
	}
	if (pid == 0)
		ft_exitbltn(shell, 0);
	return (ft_chdir2(shell));
}

bool	ft_cd(t_shell *shell, t_elem *cur, int pid)
{
	if (!cur->av[1])
	{
		ft_putstr_fd("cd: missing argument\n", 2);
		shell->error_status = 2;
		if (pid == 0)
			ft_exitbltn(shell, 2);
		return (false);
	}
	if (cur->av[2])
	{
		ft_putstr_fd("cd: extra operand '", 2);
		ft_putstr_fd(cur->av[2], 2);
		ft_putstr_fd("'\n", 2);
		shell->error_status = 2;
		if (pid == 0)
			ft_exitbltn(shell, 2);
		return (false);
	}
	return (ft_chdir(shell, cur->av[1], pid));
}
