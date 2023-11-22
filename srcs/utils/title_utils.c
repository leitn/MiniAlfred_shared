/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 03:56:54 by hedubois          #+#    #+#             */
/*   Updated: 2023/10/26 04:57:38 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_toilet(void)
{
	char	*av0;

	av0 = malloc(sizeof(char) * 7);
	av0[0] = 't';
	av0[1] = 'o';
	av0[2] = 'i';
	av0[3] = 'l';
	av0[4] = 'e';
	av0[5] = 't';
	av0[6] = '\0';
	return (av0);
}

char	*ft_minialfred(void)
{
	char	*av1;

	av1 = malloc(sizeof(char) * 11);
	av1[0] = 'M';
	av1[1] = 'i';
	av1[2] = 'n';
	av1[3] = 'i';
	av1[4] = 'A';
	av1[5] = 'l';
	av1[6] = 'f';
	av1[7] = 'r';
	av1[8] = 'e';
	av1[9] = 'd';
	av1[10] = '\0';
	return (av1);
}

char	*ft_option1(void)
{
	char	*av2;

	av2 = malloc(sizeof(char) * 3);
	av2[0] = '-';
	av2[1] = 'f';
	av2[2] = '\0';
	return (av2);
}

char	*ft_option2(void)
{
	char	*av4;

	av4 = malloc(sizeof(char) * 3);
	av4[0] = '-';
	av4[1] = 'F';
	av4[2] = '\0';
	return (av4);
}

void	ft_print_titl(t_shell *shell)
{
	char	**av;
	char	*path;
	pid_t	pid;

	av = ft_av();
	path = ft_path();
	pid = fork();
	if (pid == 0)
		execve(path, av, shell->env->envp);
	waitpid(pid, NULL, 0);
	ft_free_str_array(av);
	free(path);
}
