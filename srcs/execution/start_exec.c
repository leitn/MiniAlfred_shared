/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:41:22 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/23 16:57:15 by letnitan         ###   ########.fr       */
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

int	ft_close_fds(t_shell *shell, t_elem *cur)
{
	int		i;

	i = 0;
	if (shell->tree->count_pipe > 0)
	{
		while (i <= shell->tree->count_pipe)
		{
			printf("\ndans close_fds boucle while pipe\n");
			if (shell->pipe[i])
			{
				close(shell->pipe[i][0]);
				close(shell->pipe[i][1]);
			}
			i++;
		}
	}
	while (cur)
	{
		printf("Dans close_fd boucle cur->fd\n");
		if (cur->fd_rd != 0)
			close(cur->fd_rd);
		if (cur->fd_wr != 1)
			close(cur->fd_wr);
		cur = cur->next;
	}
	return (0);
}

int	dup_no_pipe(t_shell *shell, t_elem *cur, int i)
{
	printf("\nDans dup_no_pipe\n");
	i = 0;
	if (shell->tree->count_pipe > 0)
	 	ft_close_pipes(shell);
	if (cur->fd_rd != 0)
	{
		if (dup2(cur->fd_rd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("\nErrorDup2 : invalid fd\n", 2);
			g_error = 155;
			return (155);
		}
		close(cur->fd_rd);
	}
	if (cur->fd_wr != 1)
	{
		printf("\n DUP2 fd-> == %i et STDOUT\n", cur->fd_wr);
		if (dup2(cur->fd_wr, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("\nErrorDup2 : invalid fd\n", 2);
			g_error = 155;
			return (155);
		}
		close(cur->fd_wr);
	}
	return (0);
}

int	dup_pipe_rd(t_shell *shell, t_elem *cur, int i)
{
	if (shell->pipe[i - 1])
	{
		if (dup2(shell->pipe[i - 1][0], cur->fd_rd) == -1)
		{
			ft_putstr_fd("\nErrorDup2 : invalid fd\n", 2);
			g_error = 155;
			return (155);
		}
	}
	else
	{
		ft_putstr_fd("\nErrorDup2 : pipe error\n", 2);
		g_error = 156;
		return (156);
	}
	return (0);
}

int	dup_pipe_wr(t_shell *shell, t_elem *cur, int i)
{
	if (shell->pipe[i])
	{
		if(dup2(shell->pipe[i][1], cur->fd_wr) == -1)
		{

			ft_putstr_fd("\nErrorDup2 : invalid fd\n", 2);
			g_error = 155;
			return (155);
		}
	}
	else
	{
		ft_putstr_fd("\nErrorDup2 : pipe error\n", 2);
		g_error = 156;
		return (156);
	}
	return (0);
}

int	ft_execve (t_shell *shell,t_elem *cur,int i)
{
	if (cur->fd_wr !=-2 && cur->fd_rd != -2)
		dup_no_pipe(shell, cur, i);
	else if (cur->fd_rd == -2 && shell->tree->count_pipe > 0)
		dup_pipe_rd(shell, cur, i);
	else if (cur->fd_wr == -2  && shell->tree->count_pipe > 0)
		dup_pipe_wr(shell, cur, i);
	ft_close_fds(shell, cur);
	if (ft_isbltn(shell, cur, i) == false)
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

// exe_not_last
// exec_last (pour le code d'erreur)
// dup pipe rd : NE JAMAIS ARRIVER ICI POUR LE NOEUD 1 DE LA CHAINE DE CMDS SINON SEGFAULT

int	ft_exec(t_shell *shell, t_elem *cur)
{
	int i = -1;
	ft_init_pipes(shell);
	while(cur && i < shell->tree->count_pipe)
	{
		i++;
		printf("\ni = %i\n", i);
		printf("\nBefore exec\n----\nCOMMAND av[0] == %s\nfd_rd == %i, fd_wr == %i\n", cur->av[0], cur->fd_rd, cur->fd_wr);
		if (cur->fd_wr == -1 || cur->fd_rd == -1)
			return(ft_putstr_fd("fd error\n", 2), 42);
		// if (cur->hd_name != NULL)
		// 	cur->fd_rd = open(cur->hd_name, O_RDONLY);
		ft_signals();
		shell->pids[i] = fork();
		if (shell->pids[i] == -1)
		{
			ft_close_pipes(shell);
			return (1);
		}
		if (shell->pids[i] == 0)
			ft_execve(shell, cur, i);
		if (cur->next)
			cur = cur->next;
	}
	ft_close_fds(shell, cur);
	ft_wait_children(shell);
	cur = shell->tree->first;
	cur->hd_name = NULL;
	while(cur)
	{
		if (cur->hd_name != NULL)
			unlink(cur->hd_name);
		cur = cur->next;
	}
	return (0);
}


// EXEC FUNCTION ALL CASES WIP

/*

in redir :
right fds or -2.

int	ft_open_heredoc(t_elem *cur)
{
	int i = -1;
	int *fd;

	while(cur)
	{
		i++;
		char **tmpfile;
		malloc(sizeofchar* * nb_heredocs)
		if (cur->syntax == HEREDOC)
		{
			tmpfile[i] = ft_strlcpy(cur->hds_name);
			fd[i] = open(tmpfile[i], 0_RDONLY);
		}
		cur = cur->next;
	}
}

int	ft_execve (shell, cur, i)
{
	if (cur->fd_rd = -2)
	{
		dup2(shell->pipe[i - 1][0], stdin);
		close(shell->pipe[i - 1][0]);
	}
	if (cur->fd_wr = -2)
	{
		dup2(shell->pipe[i][1], stdout);
		close(shell->pipe[i][1]); // pose pas de pb selon karl mais undefined behaviour according to chatgpt
	}
	else if no -2
	{
		close(shell->pipe[i]) // mais si pas de pipe ?
		if fd_rd != 0
			dup2(cur->fd_rd, stdin); // protect
		if fr_wr != 1
			dup2(cur->fd_wr, stdout);
	}
	ft_close_pipes(shell);
	// exe_not_last
	// exec_last (pour le code d'erreur)
	if (ft_isbltn(cur) == false)
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
	init_pipes(shell);
	WHILE(cur)
	{
		i++;
		if cur->heredocname != nul
			cur->fd_rd = open(cur->hd_name, 0_RDONLY);
		shell->pids[i] = fork();
		if (pid == 0)
			ft_execve(shell, cur, i);
		cur = cur->next;
	}
	ft_close_fds(shell);
	ft_wait_children(shell);
	cur = shell->tree->first;
	while(cur)
	{
		if cur->hdname != NULL
			unlink(cur->hd_name);
		cur = cur->next;
	}
	return (0);
}

*/

/* OLD EXEC



int	ft_exec(t_shell *shell, t_elem *cur)
{
	// ft_redir(shell, cur);
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
