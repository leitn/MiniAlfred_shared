/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:41:22 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/27 13:13:32 by letnitan         ###   ########.fr       */
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
	{
		printf("\nI close this fd_rd");
		close(cur->fd_rd);
	}
	if (cur->fd_wr > 1)
	{
		printf("\nI close this fd_wr");
		close(cur->fd_wr);
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
		printf("\n/!\\boucle while close fd. Cur == %s\n", cur->av[0]);
		if (cur->fd_rd > 0)
		{
			printf("\nI close this fd_rd");
			close(cur->fd_rd);
		}
		if (cur->fd_wr > 1)
		{
			printf("\nI close this fd_wr");
			close(cur->fd_wr);
		}
		cur = cur->next;
	}
	printf("JE SORS DE FD_CLOSE_FD\n");
	return (0);
}

int	dup_no_pipe(t_shell *shell, t_elem *cur, int i)
{
	(void)shell;
	printf("dup_no_pipe %i\n", i);
	i = 0;
	if (cur->fd_rd != 0 && cur->fd_rd > 0)
	{
		if (dup2(cur->fd_rd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("\nErrorDup2 : invalid fd_rd in dupnopipe\n", 2);
			g_error = 155;
			return (155);
		}
	}
	if (cur->fd_wr != 1 && cur->fd_wr > 1)
	{
		if (dup2(cur->fd_wr, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("\nErrorDup2 : invalid fd_wr in dupnopipe\n", 2);
			g_error = 155;
			return (155);
		}
	}
	return (0);
}

int	dup_pipe_rd(t_shell *shell, int i)
{
	// ft_putstr_fd("\n in dup_pipe_rd\n", 2);
	// printf("i == %i\n", i);
	printf("dup_pipe_rd %i\n", i);
	if (dup2(shell->pipe[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("\nErrorDup2 : invalid fd in dup_pipe_rd\n", 2);
		g_error = 155;
		return (155);
	}
	return (0);
}

int	dup_pipe_wr(t_shell *shell, int i)
{
	errno = 0;
	printf("dup_pipe_wr %i\n", i);
	if (dup2(shell->pipe[i][1], STDOUT_FILENO) == -1)
	{
		perror("Error Dup2");
		printf("\nCaribou\nPipe[%i][1] == %i\n", i, shell->pipe[i][1]);
		ft_putstr_fd("\nErrorDup2 : invalid fd in dup_pipe_wr", 2);
		printf("%i\n", i);
		g_error = 155;
		return (155);
	}
	// close(shell->pipe[i][1]);
	// ft_close_fds(shell, shell->tree->first);
	return (0);
}

int	ft_execve (t_shell *shell, t_elem *cur, int i)
{
	// printf("\ncur-av[0] == %s\n", cur->av[0]);
	printf("\nPassage %i\n", i);
	if (cur->fd_wr != -2 || cur->fd_rd != -2)
		dup_no_pipe(shell, cur, i);
	if (cur->fd_rd == -2 && shell->tree->count_pipe > 0)
		dup_pipe_rd(shell, i);
	if (cur->fd_wr == -2  && shell->tree->count_pipe > 0)
		dup_pipe_wr(shell, i);
	ft_close_fds(shell, shell->tree->first);
	printf("\nEXECVE %i of cur->av[0] == %s\n", i, cur->av[0]);
	if (ft_isbltn(shell, cur, 0) == false)
	{
		ft_putstr_fd("\nJust Before Execution with EXECVE\n", 2);
		if (execve(cur->path, cur->av, shell->env->envp) == -1)
		{
			ft_putstr_fd(cur->av[0], 2);
			ft_putstr_fd(": ", 2);
			ft_error(CMD);
			return (1);
		}
		printf("\nFinished execve %i \n", i);
	}
	return (0);
}

int	ft_exec(t_shell *shell, t_elem *cur)
{
	int i = -1;
	ft_init_pipes(shell);
	while (cur && i < shell->tree->count_pipe)
	{
		i++;
		printf("\nBefore exec\n----\nCOMMAND av[0] == %s\nfd_rd == %i, fd_wr == %i\n", cur->av[0], cur->fd_rd, cur->fd_wr);
		if (cur->fd_wr == -1 || cur->fd_rd == -1)
			return (ft_putstr_fd("fd error\n", 2), 42); //gestion erreur
		shell->pids[i] = fork();
		ft_signals_inchildren();
		if (shell->pids[i] == -1)
		{
			printf("tessssssssssst\n");
			ft_close_pipes(shell);
			return (1);
		}
		if (cur->hd_name != NULL)
			cur->fd_rd = open(cur->hd_name, O_RDONLY | O_EXCL);
		if (shell->pids[i] == 0)
			ft_execve(shell, cur, i); //exit
		// ft_mini_close(shell, cur, i);
		printf("\nI'm out of ft_execve\n");
		if (cur->hd_name != NULL)
				unlink(cur->hd_name);
		if (cur->next)
			cur = cur->next;
	}
	printf("\nI'm out of the while\n");
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
