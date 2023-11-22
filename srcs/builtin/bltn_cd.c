/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 03:47:57 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/06 15:15:45 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_chdir(t_shell *shell, char *path, int pid)
{
	char		*old_pwd;
	char		*new_pwd;
	extern int	g_error;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (false);
	ft_add_to_the_bin(old_pwd, STR, shell->bin);
	ft_update_var(shell->env, "OLDPWD", old_pwd);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: invalid path\n", 2);
		g_error = 2;
		return (false);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (false);
	ft_add_to_the_bin(new_pwd, STR, shell->bin);
	ft_update_var(shell->env, "PWD", new_pwd);
	if (pid == 0)
		exit(0);
	return (true);
}

bool	ft_cd(t_shell *shell, t_elem *cur, int pid)
{
	extern int	g_error;

	if (!cur->av[1])
	{
		ft_putstr_fd("cd: missing argument\n", 2);
		shell->exec_current = NULL;
		g_error = 2;
		return (false);
	}
	if (cur->av[2])
	{
		ft_putstr_fd("cd: extra operand '", 2);
		ft_putstr_fd(cur->av[2], 2);
		ft_putstr_fd("'\n", 2);
		g_error = 2;
		cur = cur->next;
		shell->exec_current = cur;
		return (false);
	}
	return (ft_chdir(shell, cur->av[1], pid));
}



/*SRCS	=	main.c \
			builtin/bltn_echo.c \
			builtin/bltn_exit.c \
			builtin/bltn_pwd.c \
			builtin/bltn_utils.c \
			builtin/bltn_env.c \
			builtin/bltn_cd.c \
			builtin/bltn_unset.c \
			env/env.c \
			env/env_utils.c \
			execution/exec_utils_1.c \
			execution/exec_utils2.c \
			execution/start_exec.c \
			execution/exec_simple.c \
			init_and_free/free_utils.c \
			init_and_free/init_utils.c \
			init_and_free/init_utils2.c \
			init_and_free/bin_utils.c \
			init_and_free/shlvl_utils.c \
			lexer/lexer_utils.c \
			lexer/lexer.c \
			parser/parse_utils1.c \
			parser/parse_utils2.c \
			parser/parse_utils3.c \
			parser/parser.c \
			signals/signals_utils.c \
			utils/diverses_utils.c \
			utils/error_utils.c \
			utils/ft_split.c \
			utils/title_utils.c \
			utils/title_utils2.c */
