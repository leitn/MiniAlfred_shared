/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:27:34 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 23:58:14 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error;

bool	ft_get_input(t_shell *shell)
{
	shell->input = readline("\001\033[1;95m\002 MiniAlfred $> \001\033[0m\002");
	if (!shell->input)
		return (false);
	add_history(shell->input);
	return (true);
}

void	ft_no_path_else(t_elem *tmp, t_shell *shell)
{
	if ((tmp->path == NULL) && (check_bltn(tmp) == false))
	{
		shell->error_status = 127;
		if (tmp->av && tmp->av[0])
			ft_error(tmp->av[0], NOPATH, shell);
	}
	else
	{
		shell->error_status = 0;
		if (tmp->av && tmp->av[0] && !ft_strcmp(tmp->av[0], "cd")
			&& !ft_strcmp(tmp->av[0], "unset")
			&& !ft_strcmp(tmp->av[0], "export"))
			ft_isbltn(shell, tmp, 1);
	}
}

bool	ft_exec_no_path(t_shell *shell)
{
	t_elem	*tmp;

	tmp = shell->tree->first;
	if (shell->tree->ispath == false)
	{
		while (tmp->next)
		{
			if ((tmp->path == NULL) && (check_bltn(tmp) == false))
			{
				if (tmp->av && tmp->av[0])
					ft_error(tmp->av[0], NOPATH, shell);
			}
			tmp = tmp->next;
		}
		ft_no_path_else(tmp, shell);
		return (true);
	}
	return (false);
}

int	start_alfred(t_shell *shell)
{
	if (ft_exec_no_path(shell) == true)
		return (127);
	if (shell->tree->count_pipe <= 0)
	{
		if (ft_isbltn(shell, shell->tree->first, 1) == false)
			ft_exec(shell, shell->tree->first);
	}
	else
		ft_exec(shell, shell->tree->first);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	if (ac > 1)
		ft_error(NULL, ARG, NULL);
	g_error = 0;
	(void)av;
	shell = ft_init_shell(env);
	ft_getshell(shell, 1);
	shell->error_status = 0;
	while (42)
	{
		ft_signals_inparent();
		if (!ft_get_input(shell))
			ft_exit(NULL, shell, 1);
		if (ft_parse(shell))
		{
			start_alfred(shell);
			ft_filter(shell, TREEONLY);
		}
		ft_filter(shell, TREEONLY);
	}
	ft_filter(shell, FCLEAN);
	return (0);
}
