/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:20:17 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/29 00:10:12 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp_until_equal(t_shell *shell, char *to_export)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env->envp[i])
	{
		j = 0;
		while (shell->env->envp[i][j] != '=')
		{
			if (shell->env->envp[i][j] != to_export[j])
			{
				j = -42;
				break ;
			}
			j++;
		}
		if (j != -42 && to_export[j] == '=')
			return (i);
		i++;
	}
	return (-42);
}

void	ft_replace(t_shell *shell, char *new, int index)
{
	free(shell->env->envp[index]);
	shell->env->envp[index] = ft_strcpy(new);
}

void	ft_set_new_env(t_shell *shell, char *to_add)
{
	int	size;
	int	os;

	size = ft_array_len(shell->env->envp);
	os = sizeof(char *) * (size + 1);
	size += 2;
	shell->env->envp = ft_realloc(shell->env->envp, sizeof(char *) * size, os);
	if (!shell->env->envp)
		return ;
	shell->env->envp[size - 2] = ft_strcpy(to_add);
	shell->env->envp[size - 1] = NULL;
}

bool	ft_isequal(char *to_parse)
{
	int	i;

	i = 0;
	while (to_parse[i])
	{
		if (to_parse[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool	ft_export(t_shell *shell, t_elem *cur, int pid)
{
	int	i;

	i = 1;
	while (cur->av[i])
	{
		if (ft_strcmp_until_equal(shell, cur->av[i]) != -42)
			ft_replace(shell, cur->av[i],
				ft_strcmp_until_equal(shell, cur->av[i]));
		else if (ft_isequal(cur->av[i]))
			ft_set_new_env(shell, cur->av[i]);
		if (ft_cmpbegin(cur->av[i], "PATH"))
			ft_updatepaths(shell);
		i++;
	}
	if (pid == 0)
		exit (0);
	return (true);
}
