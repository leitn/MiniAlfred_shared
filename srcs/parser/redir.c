/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:35 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/24 17:52:55 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_simpledirright(t_elem *tmp, t_red *red)
{
	t_elem	*cur;
	t_red	*redir;
	int	fd;

	cur = tmp;
	redir = red;
	printf("\n IN SIMPLEDIRRIGHT : red->av == %s\n", red->av);
	if (access(red->av, F_OK) == 0)
		fd = open(red->av, O_WRONLY | O_TRUNC);
	else
		fd = open(red->av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("can't open the file\n", 2);   //GERER ERREUR
		g_error = 42;
		return (-1);
	}
	else
		tmp->fd_wr = fd;
	return (0);
}

int	ft_doubledirright(t_elem *tmp, t_red *red)
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
		return (-1);
	}
	else
		tmp->fd_wr = fd;
	return (0);
}

int	ft_simpleleftdir(t_elem *tmp, t_red *red)
{
	t_elem *cur;

	cur = tmp;
	if (access(red->av, F_OK) == 0)
		tmp->fd_rd = open(red->av, O_RDONLY, 0777);
	else
		tmp->fd_rd = -1;
	if (tmp->fd_rd == -1)
	{
		ft_putstr_fd("\ncan't open the file\n", 2); //GERER ERREUR
		g_error = 42;
		return (-1);
	}
	return (0);
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

int	ft_open_hd(t_elem *cur, int passage_nb, t_shell *shell)
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
			return (g_error = 42, -1);
		}
		return (1);
	}
	else
	{
		close(cur->fd_rd);
		unlink(cur->hd_name);
		// cur->hd_name = ft_strjoin("tmpfile", ft_itoa(passage_nb));
		cur->hd_name = "tmpfile";
		cur->fd_rd = open(cur->hd_name, O_RDWR | O_CREAT | O_EXCL, 0777);
		if (cur->fd_rd == -1)
		{
			perror("\nperror : can't open the heredoc");
			printf("| Error Code : %d \n", errno);
			close(cur->fd_rd);
			unlink(cur->hd_name);
			return (g_error = 42, -1);
		}
	}
	return (0);
}


int	ft_heredoc(t_shell *shell, t_elem *cur, t_red *red) // changer pour prendre en compte les nouvelles listes chainees de redirs
{
	char		*line;
	static int	passage_nb = 0;

	passage_nb++;
	if(shell->tree->count_pipe > 0)
		printf("\nPipes Alert. This is the av[0] cmd of this hd : %s\n", red->av);
	if (passage_nb <= cur->nbr_heredocs)
		ft_open_hd(cur, passage_nb, shell);
	printf("\ncur->fd_rd : %i\n", cur->fd_rd);
	shell->ss = true;
	while (1)
	{
		ft_signals_inhd();
		line = readline("> ");
		if (!line)
			return (1);
		if (ft_is_eof(cur->redirs->av, line))
			return (close(cur->fd_rd), 0);
		else
		{
			ft_putstr_fd(line, cur->fd_rd);
			ft_putstr_fd("\n", cur->fd_rd);
		}
	}
	return (0);
}

int	ft_doubledirleft(t_shell *shell, t_elem *tmp, t_red *redirs)
{
	ft_heredoc(shell, tmp, redirs);
	return(0);
	// wow cette fonction ne sert plus a rien
}
