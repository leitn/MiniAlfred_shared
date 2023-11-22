/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:37 by hedubois          #+#    #+#             */
/*   Updated: 2023/10/24 15:13:49 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_init_bin(t_shell *shell)
{
	shell->bin = malloc(sizeof(t_bin));
	if (!shell->bin)
		return (false);
	shell->bin->isempty = true;
	shell->bin->first = NULL;
	return (true);
}

void	ft_add_to_the_bin(void *waste, t_type type, t_bin *bin)
{
	t_waste	*collected;
	t_waste	*tmp;

	collected = malloc(sizeof(t_waste));
	if (!collected)
		return ;
	collected->waste = waste;
	collected->type = type;
	collected->next = NULL;
	if (bin->isempty)
	{
		bin->first = collected;
		bin->isempty = false;
		return ;
	}
	tmp = bin->first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = collected;
}

void	ft_free_waste(t_waste *waste)
{
	waste->next = NULL;
	if (waste->type == STR)
		free((char *)waste->waste);
	if (waste->type == INTARR)
		free((int *)waste->waste);
	if (waste->type == STRARR)
		ft_free_str_array((char **)waste->waste);
	free(waste);
	waste = NULL;
}

void	ft_empty_the_bin(t_bin *bin)
{
	t_waste	*tmp1;
	t_waste	*tmp2;

	if (bin->isempty)
		return ;
	tmp1 = bin->first;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		ft_free_waste(tmp1);
		tmp1 = tmp2;
	}
	bin->isempty = true;
}
