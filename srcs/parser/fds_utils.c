#include "../../include/minishell.h"

// verifie si le dernier redir est un outfile
bool	ft_check_outfile(t_elem *cur)
{
	t_red	*tmp;

	tmp = cur->redirs;
	if (tmp == NULL)
		return(false);
	while (tmp)
	{
		if (tmp->syn == SIMPLEREDIRRIGHT || tmp->syn == DOUBLEREDIRRIGHT)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	ft_complex_fds(t_shell *shell)
{
	t_red	*tmpr;
	t_elem	*tmpe;
	int		i;

	tmpe = shell->tree->first;
	i = 0;
	// printf("\nDANS COMPLEX FD IN REDIRS\n");
	while(tmpe)
	{
		i++;
		// if (tmp->av)
		// 	printf("\n Passage %i\ntmp->av[0] == %s\ntmp->path  == %s", i, tmp->av[0], tmp->path);
		tmpr = tmpe->redirs;
		while(tmpr)
		{
			// printf ("\nBOUCLE REDIRS\n");
			if (tmpr->syn == SIMPLEREDIRRIGHT)
				ft_simpledirright(tmpe, tmpr);
			if (tmpr->syn == DOUBLEREDIRRIGHT)
				ft_doubledirright(tmpe, tmpr);
			if (tmpr->syn == SIMPLEREDIRLEFT)
				ft_simpleleftdir(tmpe, tmpr);
			if (tmpr->syn == DOUBLEREDIRLEFT)
				ft_doubledirleft(shell, tmpe, tmpr);
			tmpr = tmpr->next;
		}
		if (i > 1)
			tmpe->fd_rd = -2;
		if (tmpe->next && ft_check_outfile(tmpe) == false)
			tmpe->fd_wr = -2;
		tmpe = tmpe->next;
	}
	// printf("\n\n------------------------------\n\n");
	return (0);
}

	// printf("\ntmp->av[0] == %s\ntmp->av[1] == %s\n", tmp->av[0], tmp->av[1]);
	// printf("\nAfter ft_redir : tmp->av[0] == %s, cur->fd_rd == %i, cur->fd_wr == %i\n", shell->tree->first->av[0], shell->tree->first->fd_rd, shell->tree->first->fd_wr);

void	ft_manage_fds(t_shell *shell)
{
	t_elem	*tmp;

	tmp = shell->tree->first;
	tmp->hd_name = NULL;
	while (tmp)
	{
		tmp->fd_rd = 0;
		tmp->fd_wr = 1;
		tmp = tmp->next;
	}
	// if (shell->tree->redir || shell->tree->pipe)
	ft_complex_fds(shell);
}

