/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:39:24 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 00:02:15 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_init_tree(t_shell *shell)
{
	t_head	*tree;

	tree = ft_calloc(sizeof(t_head), 1);
	if (!tree)
		return (false);
	shell->tree = tree;
	shell->tree->pipe = false;
	shell->tree->count_pipe = 0;
	shell->tree->redir = false;
	shell->isthere = true;
	return (true);
}

bool	ft_get_env_utils(t_env *en, t_bin *bin)
{
	if (!ft_get_paths(en, bin))
		return (false);
	return (true);
}

char	*ft_init_current(char *cur_env)
{
	char	*new;
	int		i;

	if (ft_isshlvl(cur_env))
		return (ft_write_shlvl(cur_env));
	new = ft_calloc(sizeof(char), (ft_strlen(cur_env) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (cur_env[i])
	{
		new[i] = cur_env[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

bool	ft_init_envp(t_shell *shell, char **env)
{
	int		i;

	i = 0;
	if (!env[0])
		return (ft_setbasicenv(shell));
	while (env[i])
		i++;
	shell->env->envp = ft_calloc(sizeof(char *), (i + 1));
	if (!shell->env->envp)
		return (false);
	i = 0;
	while (env[i])
	{
		shell->env->envp[i] = ft_init_current(env[i]);
		if (!shell->env->envp[i])
			return (false);
		i++;
	}
	shell->env->envp[i] = NULL;
	return (true);
}

t_shell	*ft_init_shell(char **env)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		exit(EXIT_FAILURE);
	shell->isthere = false;
	shell->input = NULL;
	if (!ft_init_bin(shell))
		exit (EXIT_FAILURE);
	shell->env = ft_calloc(sizeof(t_env), 1);
	if (!shell->env)
		exit (EXIT_FAILURE);
	if (!ft_init_envp(shell, env) || !ft_get_env_utils(shell->env, shell->bin))
	{
		ft_filter(shell, FCLEAN);
		exit (EXIT_FAILURE);
	}
	return (shell);
}
