/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:09:26 by letnitan          #+#    #+#             */
/*   Updated: 2023/10/22 05:57:37 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_env(t_shell *shell, char **env);



/*
int execve(const char *path, char *const argv[], char *const envp[]);
*/


/*


Dans t_shell *shell :
t_env			*env;

Dans t_env *env :

typedef struct s_env
{
	char	**envp;
	char	*home;
	char	*pwd;

}	t_env;




Code d'inspi :

void	parse_env(t_list **envl --> shell->env->envp[], char **env)
{
	t_list	*new;
	int		shlvl;
	int		i;

	i = 0;
	*envl = NULL;


	new = init_entry("?begin", -1);
	ft_lstadd_back(envl, new);
	while (env[i])
	{
		new = init_entry(env[i], 2);
		if (ft_strcmp(((t_env *)new->content)->var, "SHLVL") == 0)
		{
			shlvl = ft_atoi(((t_env *)new->content)->value);
			shlvl++;
			free(((t_env *)new->content)->value);
			((t_env *)new->content)->value = ft_itoa(shlvl);
		}
		ft_lstadd_back(envl, new);
		i++;
	}
	add_env("_", ft_strdup("./minishell"), envl, 1);
}


FONCTIONS AFFILIEES EXISTANT DEJA
bool	ft_get_env(t_env *en)
{
	if (!ft_get_home(en))
		return (false);
	if (!ft_get_pwd(en))
		return (false);
	return (true);
}

char	*ft_returnenv(char *cmd, int index)
{
	char	*getenvp;
	int		i;

	i = index + 1;
	while(cmd[i] && (cmd[i] != ' ' || cmd[i] != '"'
		|| cmd[i] == 34 || cmd[i] == '$'))
		i++;
	i -= (index + 2);
	getenvp = malloc(sizeof(char) * i + 1);
	if (!getenvp)
		return (NULL);
	i = 0;
	index++;
	while (cmd[index] && !ft_isspace(cmd[index]) && !ft_issyntax(cmd[index]))
	{
		if (cmd[index] == 34 || cmd[index] == 39 || cmd[index] == '$')
			break ;
		getenvp[i] = cmd[index];
		i++;
		index++;
	}
	getenvp[i] = '\0';
	return (getenvp);
}

 */
