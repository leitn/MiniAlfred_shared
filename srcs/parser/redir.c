/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:35 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/27 15:03:28 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_simpledirright(t_elem *tmp, t_red *red)
{
	t_elem	*cur;
	t_red	*redir;

	cur = tmp;
	redir = red;
	// printf("\n IN SIMPLEDIRRIGHT : red->av == %s\n", red->av);
	if (access(red->av, F_OK) == 0)
		tmp->fd_wr = open(red->av, O_WRONLY | O_TRUNC);
	else
		tmp->fd_wr = open(red->av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp->fd_wr == -1)
	{
		ft_putstr_fd("can't open the file\n", 2);   //GERER ERREUR
		g_error = 42;
		return (false);
	}
	return (true);
}

bool	ft_doubledirright(t_elem *tmp, t_red *red)
{
	int	fd;

	if (access(red->av, F_OK) == 0) //no idea
		fd = open(red->av, O_WRONLY | O_APPEND);
	else
		fd = open(red->av, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("can't open the file\n", 2); // GERER ERREUR
		tmp->fd_wr = fd;
		g_error = 42;
		return (false);
	}
	else
		tmp->fd_wr = fd;
	return (true);
}

bool	ft_simpleleftdir(t_elem *tmp, t_red *red)
{
	t_elem *cur;

	cur = tmp;
	if (access(red->av, F_OK) == 0)
		tmp->fd_rd = open(red->av, O_RDONLY, 0777);
	else
		tmp->fd_rd = -1;
	if (tmp->fd_rd == -1)
	{
		ft_putstr_fd("MiniAlfred: ", 2);
		ft_putstr_fd(red->av, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_error = 42;
		return (false);
	}
	return (true);
}

bool	ft_is_eof(char *eof, char *str) //strcmp a la place ?
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

char	*ft_strjoin(char *s1, char *s2)
{
	char				*str;
	size_t				lentotal;
	int	i;
	int	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lentotal = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(sizeof(char) * (lentotal + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && i <= ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && j <= ft_strlen(s2))
		str[i++] = s2[j++];
	str[lentotal] = '\0';
	return (str);
}

size_t	ft_countchar(int n)
{
	size_t			i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	if (n < 0)
	{
		nb = n * (-1);
		i++;
	}
	else
		nb = n;
	while (nb != 0 || i == 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n, t_shell *shell)
{
	size_t			i;
	size_t			j;
	char			*str;
	long			nb;

	i = ft_countchar(n);
	nb = n;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_add_to_the_bin(str, STR, shell->bin);
	j = 0;
	if (n < 0)
	{
		str[j++] = '-';
		nb = nb * (-1);
	}
	str[i] = '\0';
	while (i > j)
	{
		str[--i] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}

bool	ft_open_hd(t_elem *cur, int passage_nb, t_shell *shell)
{
	// printf("\nIn ft_open_hd\n");
	if (cur->hd_name == NULL)
	{
		cur->hd_name = ft_strjoin("tmpfile", ft_itoa(passage_nb, shell));
		cur->fd_rd = open(cur->hd_name, O_RDWR | O_CREAT | O_EXCL, 0777);
		if (cur->fd_rd == -1)
		{
			perror("perror : can't open the heredoc");
			close(cur->fd_rd);
			unlink(cur->hd_name);
			return (g_error = 42, false);  //TOFIX : g_error == 42 ???
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
			printf("| Error Code : %d \n", errno);
			close(cur->fd_rd);
			unlink(cur->hd_name);
			return (g_error = 42, false); //TOFIX : g_error == 42 ???
		}
	}
	return (true);
}


bool	ft_heredoc(t_shell *shell, t_elem *cur, t_red *red)
{
	char		*line;
	static int	passage_nb = 0;
	//int			mem_stdin;

	passage_nb++;
	if (!ft_open_hd(cur, passage_nb, shell))
		return (false);
	//mem_stdin = dup(STDIN_FILENO); TOFIX open me in exec
	g_error = 0;
	ft_signals_inhd();
	while (1)
	{
		if (g_error != 0)
			break ; //TO FIX : restaurer STDIN avant de partir :)
		line = readline("> ");
		if (!line)
			return (ft_ctrld_inhd(shell, cur, red));
		if (ft_is_eof(cur->redirs->av, line))
			return (close(cur->fd_rd), true);
		else
		{
			ft_putstr_fd(line, cur->fd_rd);
			ft_putstr_fd("\n", cur->fd_rd);
		}
	}
	return (false);
}

bool	ft_doubledirleft(t_shell *shell, t_elem *tmp, t_red *redirs)
{
	return(ft_heredoc(shell, tmp, redirs));
	// wow cette fonction ne sert plus a rien
}
