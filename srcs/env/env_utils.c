/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:12:08 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/23 15:26:53 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_index(char **env, char *target)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (target[j])
		{
			if (target[j] != env[i][j])
				break ;
			j++;
		}
		if (j == ft_strlen(target))
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
