/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:09:26 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/29 21:41:49 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_deletepaths(t_shell *shell)
{
	if (shell->env->paths)
		ft_free_str_array(shell->env->paths);
	shell->env->paths = NULL;
}

void	ft_updatepaths(t_shell *shell)
{
	int		i;
	char	*casted;

	i = ft_index(shell->env->envp, "PATH");
	if (i == -1)
	{
		ft_deletepaths(shell);
		return ;
	}
	if (shell->env->paths)
		ft_free_str_array(shell->env->paths);
	casted = ft_getenv(shell->env, "PATH");
	ft_add_to_the_bin(casted, STR, shell->bin);
	shell->env->paths = ft_split(casted, ':');
}

bool	ft_setbasicenv(t_shell *shell)
{
	char		*pwd;
	static char	*prefix = "PWD=";
	static char	*shlvl = "SHLVL=1";

	shell->env->envp = malloc(sizeof(char *) * 3);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (false);
	ft_add_to_the_bin(pwd, STR, shell->bin);
	pwd = ft_strjoin(prefix, pwd);
	shell->env->envp[0] = ft_strcpy(pwd);
	shell->env->envp[1] = ft_strcpy(shlvl);
	shell->env->envp[2] = NULL;
	return (true);
}
