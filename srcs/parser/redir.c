/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:35 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/29 03:01:14 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_simpledirright(t_elem *tmp, t_red *red, t_shell *shell)
{
	t_elem	*cur;
	t_red	*redir;

	cur = tmp;
	redir = red;
	if (access(red->av, F_OK) == 0)
		tmp->fd_wr = open(red->av, O_WRONLY | O_TRUNC);
	else
		tmp->fd_wr = open(red->av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp->fd_wr == -1)
	{
		ft_putstr_fd("MiniAlfred: ", 2);
		if (tmp->av[0])
			ft_putstr_fd(tmp->av[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		shell->error_status = 1;
		return (false);
	}
	return (true);
}

bool	ft_doubledirright(t_elem *tmp, t_red *red, t_shell *shell)
{
	int	fd;

	if (access(red->av, F_OK) == 0)
		fd = open(red->av, O_WRONLY | O_APPEND);
	else
		fd = open(red->av, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("MiniAlfred: ", 2);
		if (tmp->av[0])
			ft_putstr_fd(tmp->av[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		tmp->fd_wr = fd;
		shell->error_status = 1;
		return (false);
	}
	else
		tmp->fd_wr = fd;
	return (true);
}

bool	ft_simpleleftdir(t_elem *tmp, t_red *red, t_shell *shell)
{
	t_elem	*cur;

	cur = tmp;
	if (access(red->av, F_OK) == 0)
		tmp->fd_rd = open(red->av, O_RDONLY, 0777);
	else
	{
		tmp->fd_rd = -1;
		if (tmp->av && tmp->av[0])
			ft_error(tmp->av[0], NOPATH);
		shell->error_status = 1;
		return (false);
	}
	return (true);
}

bool	ft_open_hd(t_elem *cur, int passage_nb, t_shell *shell)
{
	if (cur->hd_name == NULL)
	{
		cur->hd_name = ft_strjoin("tmpfile", ft_itoa(passage_nb, shell));
		cur->fd_rd = open(cur->hd_name, O_RDWR | O_CREAT | O_EXCL, 0777);
		if (cur->fd_rd == -1)
		{
			perror("perror : can't open the heredoc");
			close(cur->fd_rd);
			unlink(cur->hd_name);
			return (false);
		}
		return (1);
	}
	else
	{
		close(cur->fd_rd);
		unlink(cur->hd_name);
		cur->hd_name = ft_strjoin("tmpfile", ft_itoa(passage_nb, shell));
		cur->fd_rd = open(cur->hd_name, O_RDWR | O_CREAT | O_EXCL, 0777);
		if (cur->fd_rd == -1)
		{
			perror("\nperror : can't open the heredoc");
			close(cur->fd_rd);
			unlink(cur->hd_name);
			return (false);
		}
	}
	return (true);
}


bool	ft_heredoc(t_shell *shell, t_elem *cur, t_red *red)
{
	char		*line;
	static int	passage_nb = 0;
	int			save;

	passage_nb++;
	if (!ft_open_hd(cur, passage_nb, shell))
		return (false);
	g_error = 0;
	save = dup(STDIN_FILENO);
	ft_signals_inhd();
	while (1)
	{
		line = readline("> ");
		if (g_error != 0)
			break ;
		if (!line)
			return (ft_ctrld_inhd(shell, cur, red, save));
		if (ft_is_eof(red->av, line))
			return (close(save), close(cur->fd_rd), true);
		else
		{
			ft_putstr_fd(line, cur->fd_rd);
			ft_putstr_fd("\n", cur->fd_rd);
		}
	}
	if (dup2(save, STDIN_FILENO) == -1)
	{
		ft_filter(shell, FCLEAN);
		exit(EXIT_FAILURE);
	}
	return (false);
}
