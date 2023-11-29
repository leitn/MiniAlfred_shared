/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:11:29 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/29 23:51:28 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_red	*ft_write_lst_redir(t_red *crn, t_elem *cur, char *input, int *i)
{
	t_red	*new;

	new = ft_calloc(sizeof(t_red), 1);
	if (!new)
		return (NULL);
	new->syn = ft_returnredir(input, i);
	new->av = ft_write_current_av(input, i);
	if (new->syn == DOUBLEREDIRLEFT)
		cur->nbr_heredocs++;
	if (crn)
		return (crn->next = new, new);
	return (cur->redirs = new, new);
}

void	ft_quote(char *input, int *i, int *quote)
{
	if (*quote == input[*i])
		*quote = 0;
	else if (*quote == 0)
		*quote = input[*i];
}

void	ft_line_in_hd(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

bool	ft_else_open_hd(t_elem *cur, int passage_nb, t_shell *shell)
{
	close(cur->fd_rd);
	unlink(cur->hd_name);
	free(cur->hd_name);
	cur->hd_name = NULL;
	cur->hd_name = ft_strjoin("tmpfile", ft_itoa(passage_nb, shell));
	cur->fd_rd = open(cur->hd_name, O_RDWR | O_CREAT | O_EXCL, 0777);
	if (cur->fd_rd == -1)
	{
		perror("\nperror : can't open the heredoc");
		close(cur->fd_rd);
		unlink(cur->hd_name);
		return (false);
	}
	return (true);
}
