/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:11:29 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/22 22:23:19 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_red	*ft_write_lst_redir(t_red *crn, t_elem *cur, char *input, int *i)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		return (NULL);
	new->syn = ft_returnredir(input, i);
	new->av = ft_write_current_av(input, i);
	new->next = NULL;
	if (new->syn == DOUBLEREDIRLEFT)
		cur->nbr_heredocs++;
	if (crn)
		return (crn->next = new, new);
	return (cur->redirs = new, new);
}

void	ft_manage_av(char **av, int size)
{
	if (size == 0)
		av = NULL;
	else
		av[size] = NULL;
}

void	ft_print_tree(t_head *tree)
{
	t_elem	*tmp1;
	t_red	*tmp2;
	int		i = 0;
	int		j;

	tmp1 = tree->first;
	while (tmp1)
	{
		printf("#### node %i ####\n", i++);
		j = -1;
		while (tmp1->av[++j])
			printf("av[%i] == %s\n", j, tmp1->av[j]);
		if (tmp1->redirs)
		{
			printf(">>>>> REDIRS\n");
			tmp2 = tmp1->redirs;
			j = 0;
			while (tmp2)
			{
				printf("redir[%i] == %s, token == %i\n", j++, tmp2->av, tmp2->syn);
				tmp2 = tmp2->next;
			}
		}
		tmp1 = tmp1->next;
	}
}


