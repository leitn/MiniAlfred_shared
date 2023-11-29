/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:54:13 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/29 21:54:30 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_env(t_shell *shell)
{
	if (shell->env->paths)
		ft_free_str_array(shell->env->paths);
	if (shell->env->envp)
		ft_free_str_array(shell->env->envp);
	free(shell->env);
	shell->env = NULL;
}

void	ft_filter(t_shell *shell, t_filter to_free)
{
	if (shell->input && to_free != TREEONLY)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->isthere && to_free != INPONLY)
	{
		ft_free_tree(shell->tree);
		shell->tree = NULL;
		shell->isthere = false;
	}
	if (!shell->bin->isempty)
		ft_empty_the_bin(shell->bin);
	if (to_free == FCLEAN)
	{
		free(shell->bin);
		ft_free_env(shell);
		free(shell);
		shell = NULL;
	}
}
