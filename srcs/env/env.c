/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:09:26 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/29 00:04:04 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_setbasicenv(t_shell *shell)
{
	char	*pwd;
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
