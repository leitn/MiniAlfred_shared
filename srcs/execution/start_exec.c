/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:41:22 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/22 21:52:01 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_isbltn(t_shell *shell, t_elem *cur, int pid)
{
	if (ft_strcmp(cur->av[0], "echo"))
		return(ft_echo(shell, cur, pid), true);
	else if (ft_strcmp(cur->av[0], "exit"))
		return (ft_exit(cur, shell), true);
	else if (ft_strcmp(cur->av[0], "cd"))
		return (ft_cd(shell, cur, pid), true);
	else if (ft_strcmp(cur->av[0], "export"))
		return (ft_export(shell, cur), true);
	else if (ft_strcmp(cur->av[0], "unset"))
		return (ft_unset(shell, cur, pid), true);
	else if (ft_strcmp(cur->av[0], "env"))
		return (ft_env(shell, cur, pid), true);
	else if (ft_strcmp(cur->av[0], "pwd"))
		return(ft_pwd(shell, cur, pid), true);
	return (false);
}
/*
// Mettre la boucle des dup2 dans une fonction a part
bool	ft_exec_simple(t_shell *shell, t_elem *cur)
{
	pid_t	pid;
	t_elem	*tmp;

	ft_putstr_fd("\nFT_EXEC_SIMPLE\n", 2);
	tmp = cur;
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		tmp = cur;
		while (tmp->next && tmp->after != NO && tmp->after != PIPE)
		{
			if (tmp->after == DOUBLEREDIRLEFT)
			{
				if(dup2(tmp->fd_rd, STDIN_FILENO) == -1 || dup2(tmp->fd_wr, STDOUT_FILENO) == -1)
				{
					ft_putstr_fd("\nError dup2 '<<''\n", 2);
					return (false);
				}
				close(tmp->fd_rd);
			}
			if (tmp->after == SIMPLEREDIRLEFT)
			{
				if(dup2(tmp->fd_rd, STDIN_FILENO) == -1)
				{
					ft_putstr_fd("\nError dup 2 '<'\n", 2);
					return (false);
				}
			}
			if (tmp->after == SIMPLEREDIRRIGHT || tmp->after == DOUBLEREDIRRIGHT)
			{
				if(dup2(tmp->fd_wr, STDOUT_FILENO) == -1)
				{
					ft_putstr_fd("\nError dup2 '>' '>>'\n", 2);
					return (false);
				}
				close(tmp->fd_rd);
			}
			tmp = tmp->next;
		}
		if (execve(cur->path, cur->av, shell->env->envp) == -1)
		{
			ft_putstr_fd(cur->av[0], 2);
			ft_putstr_fd(": ", 2);
			ft_error(CMD);
		}
	}
	if (tmp->after == DOUBLEREDIRLEFT)
		close(tmp->fd_rd);
	waitpid(pid, NULL, 0);
	printf("cur->path == %s, cur->av[0] == %s, cur-av[1] == %s\n", cur->path, cur->av[0], cur->av[1]);
	if (cur->next)
		return (true);
	return (false);
}

bool	is_there_hd(t_elem *first)
{
	t_elem *tmp;

	tmp = first;
	while (tmp->next)
	{
		if (tmp->after == DOUBLEREDIRLEFT || tmp->before == DOUBLEREDIRLEFT)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	ft_exec(t_shell *shell, t_elem *cur)
{
	ft_redir(shell, cur);
	if (is_there_hd(shell->tree->first) == false)
	{
		if ((check_bltn(shell->tree->first) == false) && !shell->tree->pipe)
			return (ft_exec_simple(shell, cur));
		else if ((check_bltn(shell->tree->first) == true) && !shell->tree->pipe)
			return (ft_isbltn(shell, cur, -1));
		else
			return (ft_exec_pipe(shell, cur));
	}
	else
		return(0);
}

 */
