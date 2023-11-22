/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:44:23 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/22 21:09:31 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_write_pipe(t_shell *shell, t_elem *cur, char *input, int *i)
{
	*i += 1;
	while (input[*i] == ' ')
		*i += 1;
	ft_write_cmd(cur, input, i);
	shell->tree->pipe = true;
	shell->tree->count_pipe++;
	return (true);
}

bool	ft_write_no(t_elem *cur, char *input, int *i)
{
	ft_write_cmd(cur, input, i);
	return (true);
}

void	ft_write_path(t_shell *shell, t_elem *cur)
{
	cur->path = NULL;
	if (!access(cur->av[0], F_OK | X_OK))
	{
		cur->path = ft_strcpy(cur->av[0]);
		return ;
	}
	else if (ft_is_a_builtin(cur->av[0]))
	{
		cur->path = malloc(sizeof(char) * 1);
		if(!cur->path)
			return ;
		cur->path[0] = '\0';
		return ;
	}
	else
		cur->path = init_path(shell, cur);
	if (!cur->path)
	{
		cur->path = malloc(sizeof(char) * 1);
		if(!cur->path)
			return ;
		cur->path[0] = '\0';
	}
}

/* Redige la branche actuelle, a l'aide des fonctions
du dessus en fonction de l'element syntaxique commencant
la commande */
bool	ft_write_elem(t_shell *shell, int *i)
{
	t_elem	*cur;
	bool	rtrn;

	cur = malloc(sizeof(t_elem));
	if (!cur)
		return (false);
	if (ft_issyntax(shell->input[*i]) == PIPE)
		rtrn = ft_write_pipe(shell, cur, shell->input, i);
	else
		rtrn = ft_write_no(cur, shell->input, i);
	if (rtrn == true)
		return (ft_add_elem(shell, cur), true);
	free(cur);
	return (false);
}
