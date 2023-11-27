/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:41:22 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/27 15:44:13 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_isbltn(t_shell *shell, t_elem *cur, int pid)
{
	if (cur->av)
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
	}
	return (false);
}

void	ft_mini_close(t_shell *shell, t_elem *cur, int i)
{
	if (i)
	{
		close(shell->pipe[i - 1][0]);
		close(shell->pipe[i - 1][1]);
	}
	if (cur->fd_rd > 0)
		close(cur->fd_rd);
	if (cur->fd_wr > 1)
		close(cur->fd_wr);
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

int	dup_no_pipe(t_shell *shell, t_elem *cur, int i)
{
	(void)shell;
	i = 0;
	if (cur->fd_rd != 0 && cur->fd_rd > 0)
	{
		if (dup2(cur->fd_rd, STDIN_FILENO) == -1)
		{
			perror("Error Dup2");
			// ft_putstr_fd("\nErrorDup2 : invalid fd_rd in dupnopipe\n", 2);
			g_error = 155;
			return (155);
		}
	}
	if (cur->fd_wr != 1 && cur->fd_wr > 1)
	{
		if (dup2(cur->fd_wr, STDOUT_FILENO) == -1)
		{
			perror("Error Dup2");
			// ft_putstr_fd("\nErrorDup2 : invalid fd_wr in dupnopipe\n", 2);
			g_error = 155;
			return (155);
		}
	}
	return (0);
}

int	dup_pipe_rd(t_shell *shell, int i)
{
	if (dup2(shell->pipe[i - 1][0], STDIN_FILENO) == -1)
	{
		perror("Error Dup2");
		// ft_putstr_fd("\nErrorDup2 : invalid fd in dup_pipe_rd\n", 2);
		g_error = 155;
		return (155);
	}
	return (0);
}

int	dup_pipe_wr(t_shell *shell, int i)
{
	errno = 0;
	if (dup2(shell->pipe[i][1], STDOUT_FILENO) == -1)
	{
		perror("Error Dup2");
		// ft_putstr_fd("\nErrorDup2 : invalid fd in dup_pipe_wr", 2);
		g_error = 155;
		return (155);
	}
	return (0);
}

int	ft_execve (t_shell *shell, t_elem *cur, int i)
{
	if (cur->fd_wr != -2 || cur->fd_rd != -2)
		dup_no_pipe(shell, cur, i);
	if (cur->fd_rd == -2 && shell->tree->count_pipe > 0)
		dup_pipe_rd(shell, i);
	if (cur->fd_wr == -2  && shell->tree->count_pipe > 0)
		dup_pipe_wr(shell, i);
	ft_close_fds(shell, shell->tree->first);
	if (ft_isbltn(shell, cur, 0) == false)
	{
		if (execve(cur->path, cur->av, shell->env->envp) == -1)
		{
			ft_putstr_fd(cur->av[0], 2);
			ft_putstr_fd(": ", 2);
			ft_error(CMD);
			return (1);
		}
	}
	return (0);
}

int	ft_exec(t_shell *shell, t_elem *cur)
{
	int i = -1;
	ft_init_pipes(shell);
	while (cur && i < shell->tree->count_pipe)
	{
		if (cur->fd_wr == -1 || cur->fd_rd == -1)
			return (ft_putstr_fd("fd error\n", 2), 42); //gestion erreur
		shell->pids[++i] = fork();
		ft_signals_inchildren();
		if (shell->pids[i] == -1)
			return (ft_close_pipes(shell), 1);
		if (cur->hd_name != NULL)
			cur->fd_rd = open(cur->hd_name, O_RDONLY | O_EXCL);
		if (shell->pids[i] == 0)
			ft_execve(shell, cur, i); //exit
		if (cur->hd_name != NULL)
				unlink(cur->hd_name);
		if (cur->next)
			cur = cur->next;
	}
	ft_close_fds(shell, shell->tree->first);
	ft_wait_children(shell);
	cur = shell->tree->first;
	while(cur)
	{
		if (cur->hd_name != NULL)
			unlink(cur->hd_name);
		cur = cur->next;
	}
	return (0);
}
