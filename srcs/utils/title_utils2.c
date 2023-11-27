/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 04:23:07 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/27 23:14:07 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_smblock(void)
{
	char	*av3;

	av3 = malloc(sizeof(char) * 8);
	av3[0] = 's';
	av3[1] = 'm';
	av3[2] = 'b';
	av3[3] = 'l';
	av3[4] = 'o';
	av3[5] = 'c';
	av3[6] = 'k';
	av3[7] = '\0';
	return (av3);
}

char	*ft_border(void)
{
	char	*av5;

	av5 = malloc(sizeof(char) * 7);
	av5[0] = 'b';
	av5[1] = 'o';
	av5[2] = 'r';
	av5[3] = 'd';
	av5[4] = 'e';
	av5[5] = 'r';
	av5[6] = '\0';
	return (av5);
}

char	**ft_av(void)
{
	char	**av;

	av = malloc(sizeof(char *) * 7);
	if (!av)
		return (NULL);
	av[0] = ft_toilet();
	av[1] = ft_minialfred();
	av[2] = ft_option1();
	av[3] = ft_smblock();
	av[4] = ft_option2();
	av[5] = ft_border();
	av[6] = NULL;
	return (av);
}

char	*ft_path(void)
{
	static char	*path = "/usr/bin/toilet";
	char		*rtrn;
	int			i;

	rtrn = malloc(sizeof(char) * 16);
	if (!rtrn)
		return (NULL);
	i = 0;
	while (path[i])
	{
		rtrn[i] = path[i];
		i++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}
