/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:41:22 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 21:46:35 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_isbltn(t_shell *shell, t_elem *cur, int pid)
{
	if (cur->av && cur->av[0])
	{
		if (ft_strcmp(cur->av[0], "echo"))
			return (ft_echo(shell, cur, pid), true);
		else if (ft_strcmp(cur->av[0], "exit"))
			return (ft_exit(cur, shell, pid), true);
		else if (ft_strcmp(cur->av[0], "cd"))
			return (ft_cd(shell, cur, pid), true);
		else if (ft_strcmp(cur->av[0], "export"))
			return (ft_export(shell, cur, pid), true);
		else if (ft_strcmp(cur->av[0], "unset"))
			return (ft_unset(shell, cur, pid), true);
		else if (ft_strcmp(cur->av[0], "env"))
			return (ft_env(shell, cur, pid), true);
		else if (ft_strcmp(cur->av[0], "pwd"))
			return (ft_pwd(shell, cur, pid), true);
	}
	return (false);
}

void	ft_exec_final(t_elem *cur, t_shell *shell)
{
	if (cur->path == NULL && cur->av[0])
	{
		ft_error(cur->av[0], CMD, shell);
		ft_filter(shell, TREEONLY);
		ft_filter(shell, FCLEAN);
		exit(-1);
	}
	else if (execve(cur->path, cur->av, shell->env->envp) == -1)
	{
		ft_error(cur->av[0], CMD, shell);
		ft_filter(shell, FCLEAN);
		exit(-1);
	}
}

int	ft_execve(t_shell *shell, t_elem *cur, int i)
{
	if (!cur->av || !cur->av[0])
	{
		if (cur->av)
		{
			free(cur->av);
			cur->av = NULL;
		}
		ft_close_fds(shell, shell->tree->first);
		ft_free_hd(shell);
		ft_filter(shell, TREEONLY);
		ft_filter(shell, FCLEAN);
		exit (-1);
	}
	if ((cur->fd_wr != -2 && cur->fd_wr > 2)
		|| (cur->fd_rd != -2 && cur->fd_rd > 0))
		dup_no_pipe(shell, cur, i);
	if (cur->fd_rd == -2 && shell->tree->count_pipe > 0)
		dup_pipe_rd(shell, i);
	if (cur->fd_wr == -2 && shell->tree->count_pipe > 0)
		dup_pipe_wr(shell, i);
	ft_close_fds(shell, shell->tree->first);
	if (cur->av[0] && ft_isbltn(shell, cur, 0) == false)
		ft_exec_final(cur, shell);
	ft_filter(shell, FCLEAN);
	exit(1);
}

int	ft_exec(t_shell *shell, t_elem *tmp)
{
	int		i;
	t_elem	*cur;

	cur = tmp;
	i = -1;
	ft_init_pipes(shell);
	while (cur && i < shell->tree->count_pipe)
	{
		if (cur->fd_wr == -1 || cur->fd_rd == -1)
			return (ft_putstr_fd("fd error\n", 2), 42);
		shell->pids[++i] = fork();
		ft_signals_inchildren();
		if (shell->pids[i] == -1)
			return (ft_close_pipes(shell), 1);
		if (cur->hd_name != NULL)
			cur->fd_rd = open(cur->hd_name, O_RDONLY | O_EXCL);
		if (shell->pids[i] == 0)
			ft_execve(shell, cur, i);
		if (cur->next)
			cur = cur->next;
	}
	ft_close_fds(shell, shell->tree->first);
	ft_wait_children(shell);
	ft_free_hd(shell);
	return (0);
}
