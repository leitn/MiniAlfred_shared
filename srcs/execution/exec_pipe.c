/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:10:02 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/23 18:43:11 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_bltn(t_elem *cur)
{
	if (ft_strcmp(cur->av[0], "echo"))
		return(true);
	else if (ft_strcmp(cur->av[0], "exit"))
		return (true);
	else if (ft_strcmp(cur->av[0], "cd"))
		return (true);
	else if (ft_strcmp(cur->av[0], "export"))
		return (true);
	else if (ft_strcmp(cur->av[0], "unset"))
		return (true);
	else if (ft_strcmp(cur->av[0], "env"))
		return (true);
	else if (ft_strcmp(cur->av[0], "pwd"))
		return (true);
	return (false);
}

// int	ft_exec_pipe(t_shell *shell, t_elem *cur)
// {
// 	int		i;

// 	i = 0;
// 	ft_init_pipes(shell);
// 	printf("\nIN EXEC PIPE\n");
// 	while (i <= shell->tree->count_pipe)
// 	{
// 		ft_signals();
// 		shell->pids[i] = fork();
// 		if (shell->pids[i] == -1)
// 		{
// 			ft_close_pipes(shell);
// 			return (1);
// 		}
// 		printf("\nIn Ft_EXEC_PIPE. cur->arg[0] == %s\n", cur->av[0]);
// 		if (shell->pids[i] == 0 && i == 0)
// 			exec_first_node(shell, cur, shell->pipe[i]);
// 		else if (shell->pids[i] == 0 && i == shell->tree->count_pipe)
// 			exec_last_node(shell, cur, shell->pipe[i - 1]);
// 		else if (shell->pids[i] == 0 && i != shell->tree->count_pipe && i != 0)
// 			exec_middle_node(shell, cur, i);
// 		if (cur->next)
// 		{
// 			if (cur->after == PIPE || cur->after == REDIR) //insuffisant
// 				cur = cur->next;
// 			else
// 				cur = cur->next->next;
// 		}
// 		i++;
// 	}
// 	ft_close_pipes(shell);
// 	ft_wait_children(shell);
// 	return (0);
// }

void	ft_close_pipes(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->tree->count_pipe)
	{
		close(shell->pipe[i][0]);
		close(shell->pipe[i][1]);
		i++;
	}
}

void	ft_init_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while(i < shell->tree->count_pipe)
	{
		if (pipe(shell->pipe[i]) == -1)
		{
			i = 0;
			while (i < shell->tree->count_pipe)
			{
				close(shell->pipe[i][0]);
				close(shell->pipe[i][1]);
				i++;
			}
			printf("\nPipe Error\n");
		}
		i++;
	}
}

int	ft_wait_children(t_shell *shell)
{
	int			i;
	int			error_status;
	extern int	g_error;

	i = 0;
	while (i < shell->tree->count_pipe - 1)
	{
		waitpid(shell->pids[i], NULL, 0);
		i++;
	}
	waitpid(shell->pids[i], &error_status, 0);
	printf("\nwaited, shell->pids[%i]\n", i);
	if (WIFEXITED(error_status)) // means it terminated normally
		g_error = WEXITSTATUS(error_status);
	else if (WIFSIGNALED(error_status)) // means it terminated because of a signal call
		g_error = 131; //return value for signal errorI think but check it
	return (g_error);
}
