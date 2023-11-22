/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:35 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/22 21:52:59 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
int	ft_simpledirright(t_elem *tmp)
{
	int	fd;
	t_elem *cur;

	cur = tmp;
	while(cur->next)
	{
		if (access(cur->next->av[0], F_OK) == 0)
			fd = open(cur->next->av[0], O_WRONLY | O_TRUNC);
		else
			fd = open(cur->next->av[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cur = cur->next;
	}
	if (fd == -1)
	{
		ft_putstr_fd("can't open the file\n", 2);
		g_error = 42;
		return (-1);
	}
	else
		tmp->fd_wr = fd;
	return (fd);
}

int	ft_doubledirright(t_elem *tmp)
{
	int	fd;
	t_elem *cur;

	cur = tmp;
	while(cur->next)
	{
		if (access(cur->next->av[0], F_OK) == 0)
			fd = open(cur->next->av[0], O_WRONLY | O_APPEND);
		else
			fd = open(cur->next->av[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		cur = cur->next;
	}
	if (fd == -1)
	{
		ft_putstr_fd("can't open the file\n", 2);
		g_error = 42;
		return (-1);
	}
	else
		tmp->fd_wr = fd;
	return (fd);
}

int	ft_simpleleftdir(t_elem *tmp)
{
	int		fd;
	t_elem *cur;

	cur = tmp;
	while(cur->next && cur->after == REDIR)
	{
		if (tmp->after == SIMPLEREDIRLEFT)
		{
			if (access(cur->next->av[0], F_OK) == 0)
				fd = open(cur->next->av[0], O_RDONLY, 0777);
		}
		else if(tmp->after == SIMPLEREDIRRIGHT)
			fd = ft_simpledirright(cur);
		else if (tmp->after == DOUBLEREDIRRIGHT)
			fd = ft_doubledirright(cur);
		else
			fd = 0;
		cur = cur->next;
	}
	if (fd == -1)
	{
		ft_putstr_fd("\ncan't open the file\n", 2);
		g_error = 42;
		return (-1);
	}
	else
		tmp->fd_rd = fd;
	return (fd);
}

bool	ft_is_eof(char *eof, char *str)
{
	while (*str)
	{
		if (*eof == '"' || *eof == '\'')
		{
			eof++;
			continue ;
		}
		else if (*str == *eof)
		{
			str++;
			eof++;
		}
		else
			return (false);
	}
	while (*eof == '"' || *eof == '\'')
		eof++;
	return (!*eof);
}

int	ft_heredoc(t_shell *shell, t_elem *tmp)
{
	t_elem	*cur;
	pid_t	pid;
	int		fd;
	char	*line;

	cur = tmp;

	const char	*tempfile = "mytempfile.txt";
	fd = open(tempfile, O_RDWR | O_CREAT | O_EXCL, 0777);
	while (1)
	{
		if (cur->after == DOUBLEREDIRLEFT)
		{
			line = readline("> ");
			if (!line)
				return (1);
			if (ft_is_eof(cur->next->av[0], line))
			{
				close(fd);
				tmp->fd_rd = open(tempfile, O_RDONLY);
				pid = fork();
				if (pid == 0)
				{
					if (dup2(tmp->fd_rd, STDIN_FILENO) == -1)
					{
						ft_putstr_fd("\nError dup2 '<<''\n", 2);
						return (false);
					}
					if ( dup2(tmp->fd_wr, STDOUT_FILENO) == -1)
					{
						ft_putstr_fd("\nError dup2 '<<''\n", 2);
						return (false);
					}
					if (tmp->fd_rd != 0)
						close(tmp->fd_rd);
					if (tmp->fd_wr != 1)
						close(tmp->fd_wr);
					if (execve(tmp->path, tmp->av, shell->env->envp) == -1)
					{
						ft_putstr_fd(cur->av[0], 2);
						ft_putstr_fd(": ", 2);
						ft_error(CMD);
					}
				}
				if (tmp->fd_rd != 0)
					close(tmp->fd_rd);
				if (tmp->fd_wr != 1)
					close(tmp->fd_wr);
				waitpid(pid, NULL, 0);
				unlink(tempfile);
				return (0);
			}
			else
			{
				ft_putstr_fd(line, fd);
				ft_putstr_fd("\n", fd);
			}
		}
	}
	return (0);
}

int	ft_doubledirleft(t_shell *shell, t_elem *tmp)
{
	t_elem	*cur;

	cur = tmp;
	while (cur->next && cur->after != PIPE)
	{
		if (cur->after == SIMPLEREDIRRIGHT)
			tmp->fd_wr = ft_simpledirright(tmp);
		if (cur->after == DOUBLEREDIRRIGHT)
			tmp->fd_wr = ft_doubledirright(tmp);
		// if (tmp->after == SIMPLEREDIRLEFT) //Je fais quoi la ?
		// 	ft_simpleleftdir(tmp);
		cur = cur->next;
	}
	ft_heredoc(shell, tmp);
	return(0);
}

int	ft_redir(t_shell *shell,t_elem *cur)
{
	t_elem *tmp;

	tmp = cur;
	while(tmp->next)
	{
		printf("\ntmp->av[0] == %s\ntmp->av[1] == %s\n", tmp->av[0], tmp->av[1]);
		if (tmp->after == SIMPLEREDIRRIGHT)
			ft_simpledirright(tmp);
		if (tmp->after == DOUBLEREDIRRIGHT)
			ft_doubledirright(tmp);
		if (tmp->after == SIMPLEREDIRLEFT)
			ft_simpleleftdir(tmp);
		if (tmp->after == DOUBLEREDIRLEFT)
			ft_doubledirleft(shell, tmp);
		tmp = tmp->next;
	}
	printf("\nAfter ft_redir : tmp->av[0] == %s, cur->fd_rd == %i, cur->fd_wr == %i\n", shell->tree->first->av[0], shell->tree->first->fd_rd, shell->tree->first->fd_wr);
	return (0);
}
 */
