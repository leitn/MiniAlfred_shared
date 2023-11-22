#include "../../include/minishell.h"

void	ft_manage_fds(t_shell *shell)
{
	t_elem	*tmp;

	tmp = shell->tree->first;
	while (tmp)
	{
		tmp->fd_rd = 0;
		tmp->fd_wr = 1;
		tmp = tmp->next;
	}
/* 	if (shell->tree->redir || shell->tree->pipe)
		ft_complex_fds(shell); */
}