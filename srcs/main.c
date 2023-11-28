/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:27:34 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/28 15:25:48 by letnitan         ###   ########.fr       */
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

int	start_alfred(t_shell *shell)
{
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
		ft_error(NULL, ARG);
	g_error = 0;
	(void)av;
	shell = ft_init_shell(env);
	ft_getshell(shell, 1);
	// ft_print_titl(shell);
	while (42)
	{
		ft_signals_inparent();
		shell->error_status = g_error;
		if (!ft_get_input(shell))
			break ;
		shell->error_status = 0;
		if (ft_parse(shell))
		{
			start_alfred(shell);
			ft_filter(shell, TREEONLY);
		}
	}
	ft_filter(shell, FCLEAN);
	return (0);
}
