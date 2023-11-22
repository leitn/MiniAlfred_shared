/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:09:28 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/22 21:52:25 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
void	ft_putnbr_fd(int n, int fd)
{
	long b;

	b = n;
	if (b < 0)
	{
		ft_putchar_fd('-', fd);
		b = b * -1;
	}
	if (b > 9)
	{
		ft_putnbr_fd(b / 10, fd);
		ft_putnbr_fd(b % 10, fd);
	}
	else
		ft_putchar_fd(b + '0', fd);
}

bool	exec_first_node(t_shell *shell, t_elem *cur, int *fd)
{
	if (cur->after == DOUBLEREDIRLEFT || cur->after == SIMPLEREDIRLEFT)
	{
		if(dup2(cur->fd_rd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("\nError First Node\n", 2);
			return (false);
		}
	}
	if(dup2(fd[1], cur->fd_wr) == -1)
	{
		ft_putstr_fd("\nError First Node\n", 2);
		return (false);
	}
	ft_close_pipes(shell);
	if (check_bltn(cur) == false)
	{
		if (execve(cur->path, cur->av, shell->env->envp) == -1)
		{
			ft_putstr_fd(cur->av[0], 2);
			ft_putstr_fd(": ", 2);
			ft_error(CMD);
			return (false);
		}
	}
	else
		return (ft_isbltn(shell, cur, 0));
	return (true);
}

bool	exec_last_node(t_shell *shell, t_elem *cur, int *fd)
{
	if (cur->after != DOUBLEREDIRRIGHT)
	{
		if (dup2(fd[0], cur->fd_rd) == -1)
		{
			ft_putstr_fd("\nError Last Node\n", 2);
			return (false);
		}
	}
	if (cur->after == SIMPLEREDIRRIGHT)
	{
		if(dup2(cur->fd_wr, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("\nError First Node\n", 2);
			return (false);
		}
	}
	ft_close_pipes(shell);
	if (check_bltn(cur) == false)
	{
		if (execve(cur->path, cur->av, shell->env->envp) == -1)
		{
			ft_putstr_fd(cur->av[0], 2);
			ft_putstr_fd(": ", 2);
			ft_error(CMD);
			return (false);
		}
	}
	else
		return (ft_isbltn(shell, cur, 0));
	return (true);
}

bool	exec_middle_node(t_shell *shell, t_elem *cur, int i)
{
	if (cur->prev->after != DOUBLEREDIRRIGHT)
	{
		if (dup2(shell->pipe[i-1][0], cur->fd_rd) == -1
			|| dup2(shell->pipe[i][1], cur->fd_wr) == -1)
		{
			ft_putstr_fd("Error Middle Node\n", 2);
			return (false);
		}
	}
	else
	{
		if (dup2(shell->pipe[i][1], cur->fd_wr) == -1)
		{
			ft_putstr_fd("Error Middle Node\n", 2);
			return (false);
		}
	}
	ft_close_pipes(shell);
	if (check_bltn(cur) == false)
	{
		if (execve(cur->path, cur->av, shell->env->envp) == -1)
		{
			ft_putstr_fd(cur->av[0], 2);
			ft_putstr_fd(": ", 2);
			ft_error(CMD);
			return(false);
		}
	}
	else
		return(ft_isbltn(shell, cur, 0));
	return(true);
}
 */
