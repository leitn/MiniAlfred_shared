/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:44:34 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 00:08:12 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_shell *shell, t_elem *cur, int pid)
{
	int		i;
	bool	ispath;

	if (!cur->av[1])
		return ;
	if (ft_issyntax(cur->av[1][0]) == OPTION)
	{
		ft_putstr_fd("unset: this implementation take no options\n", 2);
		return ;
	}
	i = 1;
	ispath = false;
	while (cur->av[i] && !ft_issyntax(cur->av[i][0]))
	{
		if (ft_strcmp(cur->av[i], "PATH"))
			ispath = true;
		ft_delete_var(shell, cur->av[i++]);

	}
	shell->exec_current = cur->next;
	if (ispath == true)
		ft_updatepaths(shell);
	if (pid == 0)
		exit(0);
}
