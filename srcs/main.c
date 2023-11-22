/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:27:34 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/22 21:50:19 by hedubois         ###   ########.fr       */
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
	// ft_print_titl(shell);
	while (42)
	{
		ft_signals();
		if (!ft_get_input(shell))
			break ;
		if (ft_parse(shell))
		{
			// int i = 1;
			// t_elem *tmp;
			// int		j;
			// tmp = shell->tree->first;
			// while (tmp)
			// {
			// 	j = 0;
			// 	printf("tmp n°%i\n", i);
			// 	while (tmp->av[j])
			// 	{
			// 		printf("av[%i] == %s\n", j, tmp->av[j]);
			// 		j++;
			// 	}
			// 	printf("av[%i] == %s\n", j, tmp->av[j]);
			// 	printf("before == %i, after == %i\n", tmp->before, tmp->after);
			// 	printf("current path == %s\n", tmp->path);
			// 	printf("\nFD->wr == %i, FD->read == %i\n\n", tmp->fd_wr, tmp->fd_rd);
			// 	tmp = tmp->next;
			// 	i++;
			// }
			ft_print_tree(shell->tree);
			/* ft_exec(shell, shell->tree->first); */
		}
		ft_filter(shell, TREEONLY);
	}
	ft_filter(shell, FCLEAN);
	return (0);
}
