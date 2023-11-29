/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:33:40 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 18:48:17 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_isnbr(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (nbr[i] < '0' || nbr[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_atoi(char *nbr, int *result)
{
	int	i;
	int	sign;

	if (!ft_isnbr(nbr))
		return (false);
	sign = 1;
	i = 0;
	*result = 0;
	if (nbr[0] == '-')
	{
		sign = -1;
		i++;
	}
	if (nbr[0] == '+')
		i++;
	while (nbr[i])
	{
		if (*result > *result * 10 + nbr[i] - 48)
			return (false);
		*result *= 10;
		*result += nbr[i] - 48;
		i++;
	}
	*result *= sign;
	return (true);
}

void	ft_non_numeric(t_shell *shell, char *cmd)
{
	ft_putstr_fd("MiniAlfred: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_filter(shell, FCLEAN);
	exit(2);
}

bool	ft_too_many_args(t_shell *shell, int pid)
{
	ft_putstr_fd("MiniAlfred: exit: too many arguments\n", 2);
	g_error = 2;
	shell->error_status = 1;
	if (pid == 0)
		exit (1);
	return (false);
}

bool	ft_exit(t_elem *cur, t_shell *shell, int pid)
{
	extern int	g_error;
	int			exit_status;

	if (pid != 0)
		ft_putstr_fd("exit\n", 2);
	if (cur && cur->av[1])
	{
		if (!ft_atoi(cur->av[1], &exit_status))
			ft_non_numeric(shell, cur->av[1]);
		else if (cur->av[2])
			return (ft_too_many_args(shell, pid));
		ft_filter(shell, FCLEAN);
		exit(exit_status);
	}
	exit_status = shell->error_status;
	ft_filter(shell, FCLEAN);
	exit(exit_status);
}
