/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:27:34 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/25 16:26:44 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error;

bool	ft_get_input(t_shell *shell)
{
	static const char	*red = " \033[31mMiniAlfred\033[0m $> ";
	static const char	*green = " \033[32mMiniAlfred\033[0m $> ";
	extern int			g_error;

	if (g_error == 0)
		shell->input = readline(green);
	else
	{
		shell->input = readline(red);
		g_error = 0;
	}
	if (!shell->input)
		return (false);
	if (!ft_ishell(shell->input))
		add_history(shell->input);
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	if (ac > 1)
		ft_error(ARG);
	g_error = 0;
	(void)av;
	shell = ft_init_shell(env);
	ft_getshell(shell, 1);
	// ft_print_titl(shell);
	while (42)
	{
		ft_signals_inparent();
		if (!ft_get_input(shell))
			break ;
		if (ft_parse(shell))
		{
			ft_print_tree(shell->tree);
			if (shell->tree->count_pipe <= 0 && g_error != 130)
			{
				if (ft_isbltn(shell, shell->tree->first, 1) == false)
					ft_exec(shell, shell->tree->first);
			}
			else if (g_error != 130)
				ft_exec(shell, shell->tree->first);
		}
		ft_filter(shell, TREEONLY);
	}
	ft_filter(shell, FCLEAN);
	return (0);
}
