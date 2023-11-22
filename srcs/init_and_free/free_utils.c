/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:56:59 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/22 22:04:29 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_freestr(char *str)
{
	free(str);
	str = NULL;
	return (false);
}

void	ft_free_tree(t_head *tree)
{
	t_elem	*tmp1;
	t_elem	*tmp2;

	tmp1 = tree->first;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if (tmp1->av)
			ft_free_str_array(tmp1->av);
		if (tmp1->path)
			free(tmp1->path);
/* 		if (tmp1->) */
		free(tmp1);
		tmp1 = tmp2;
	}
	free(tree);
}

void	ft_free_str_array(char **strarr)
{
	char	**tmp;

	tmp = strarr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(strarr);
}

void	ft_free_env(t_shell *shell)
{
	ft_free_str_array(shell->env->paths);
	ft_free_str_array(shell->env->envp);
	free(shell->env);
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
	ft_empty_the_bin(shell->bin);
	if (to_free == FCLEAN)
	{
		ft_free_env(shell);
		free(shell->bin);
		free(shell);
	}
}
