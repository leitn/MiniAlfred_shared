/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:12:08 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 17:04:48 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_index(char **env, char *target)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_cmpbegin(env[i], target))
			return (i);
		i++;
	}
	return (-1);
}

/* fonctionne comme getenv()
(-> man 3 getenv), prend juste
env (contenu ds shell) en plus.
return la variable si elle existe,
NULL sinon. /!\ penser a free la chaine retournee */

char	*ft_getenv(t_env *env, char *target)
{
	char	*var;
	int		i;
	int		j;
	int		index;

	if (!target)
		return (NULL);
	index = ft_index(env->envp, target);
	if (index == -1)
		return (NULL);
	i = 0;
	while (env->envp[index][i] != '=')
		i++;
	var = ft_calloc(sizeof(char), (ft_strlen(env->envp[index]) - i + 1));
	if (!var)
		return (NULL);
	i++;
	j = 0;
	while (env->envp[index][i])
		var[j++] = env->envp[index][i++];
	var[j] = '\0';
	return (var);
}

/* met a jour la valeur de to_update
avec new si elle existe et renvoie true.
Renvoie false si elle n'existe pas
ou si une erreur se produit. */

bool	ft_update_var(t_env *env, char *to_update, char *new)
{
	char	*new_var;
	int		i;
	int		j;
	int		index;

	index = ft_index(env->envp, to_update);
	if (index == -1)
		return (false);
	new_var = calloc(sizeof(char), (2 + ft_strlen(to_update) + ft_strlen(new)));
	if (!new_var)
		return (false);
	i = 0;
	while (to_update[i])
	{
		new_var[i] = to_update[i];
		i++;
	}
	new_var[i++] = '=';
	j = 0;
	while (new[j])
		new_var[i++] = new[j++];
	new_var[i] = '\0';
	free(env->envp[index]);
	env->envp[index] = new_var;
	return (true);
}

bool	ft_delete_var(t_shell *shell, char *to_delete)
{
	char	**new_env;
	int		index;
	int		i;
	int		j;

	index = ft_index(shell->env->envp, to_delete);
	if (index == -1)
		return (false);
	i = 0;
	while (shell->env->envp[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i);
	if (!new_env)
		return (false);
	i = 0;
	j = 0;
	while (shell->env->envp[i])
	{
		if (!(new_env[j++] = ft_init_current(shell->env->envp[i++])))
			return (false);
		if (i == index)
			i++;
	}
	new_env[j] = NULL;
	ft_free_str_array(shell->env->envp);
	shell->env->envp = new_env;
	return (true);
}

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
