#include "../../include/minishell.h"

int	ft_complex_fds(t_shell *shell,t_elem *cur)
{
	t_elem *tmp;
	int		i;

	tmp = cur;
	i = 0;
	printf("\nDANS COMPLEX FD IN REDIRS\n");
	while(tmp)
	{
		i++;
		printf("\n Passage %i\ntmp->av[0] == %s", i, tmp->av[0]);
		while(tmp->redirs)
		{
			printf ("\nBOUCLE REDIRS\n");
			if (tmp->redirs->syn == SIMPLEREDIRRIGHT)
				ft_simpledirright(tmp, tmp->redirs);
			if (tmp->redirs->syn == DOUBLEREDIRRIGHT)
				ft_doubledirright(tmp, tmp->redirs);
			if (tmp->redirs->syn == SIMPLEREDIRLEFT)
				ft_simpleleftdir(tmp, tmp->redirs);
			if (tmp->redirs->syn == DOUBLEREDIRLEFT)
				ft_doubledirleft(shell, tmp, tmp->redirs);
			tmp->redirs = tmp->redirs->next;
		}
		if (i > 1)
			tmp->fd_rd = -2;
		else if (tmp->next && tmp->redirs == NULL)
			tmp->fd_wr = -2;
		tmp = tmp->next;
	}
	printf("\n\n------------------------------\n\n");
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
	ft_complex_fds(shell, shell->tree->first);
}

