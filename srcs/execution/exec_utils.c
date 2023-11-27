/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:10:02 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/27 14:21:19 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_bltn(t_elem *cur)
{
	if (ft_strcmp(cur->av[0], "echo"))
		return(true);
	else if (ft_strcmp(cur->av[0], "exit"))
		return (true);
	else if (ft_strcmp(cur->av[0], "cd"))
		return (true);
	else if (ft_strcmp(cur->av[0], "export"))
		return (true);
	else if (ft_strcmp(cur->av[0], "unset"))
		return (true);
	else if (ft_strcmp(cur->av[0], "env"))
		return (true);
	else if (ft_strcmp(cur->av[0], "pwd"))
		return (true);
	return (false);
}

void	ft_close_pipes(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->tree->count_pipe)
	{
		close(shell->pipe[i][0]);
		close(shell->pipe[i][1]);
		i++;
	}
}

int	ft_close_fds(t_shell *shell, t_elem *cur)
{
	int		i;

	i = 0;
	if (shell->tree->count_pipe > 0)
	{
		while (i < shell->tree->count_pipe)
		{
			close(shell->pipe[i][0]);
			close(shell->pipe[i][1]);
			i++;
		}
	}
	while (cur)
	{
		if (cur->fd_rd > 0)
			close(cur->fd_rd);
		if (cur->fd_wr > 1)
			close(cur->fd_wr);
		cur = cur->next;
	}
	return (0);
}

void	ft_init_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->tree->count_pipe)
	{
		if (pipe(shell->pipe[i]) == -1)
		{
			i = 0;
			while (i < shell->tree->count_pipe)
			{
				close(shell->pipe[i][0]);
				close(shell->pipe[i][1]);
				i++;
			}
			printf("\nPipe Error\n");
		}
		i++;
	}
}

int	ft_wait_children(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->tree->count_pipe)
	{
		waitpid(shell->pids[i], NULL, 0);
		i++;
	}
	waitpid(shell->pids[i], &shell->error_status, 0);
	ft_recast_return(shell);
	return (0);
}
