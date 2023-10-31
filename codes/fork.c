/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/10/31 10:44:58 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childprocess(t_ppx *ppx, int *pipefd)
{
	char	**argv;

	argv = ft_split(ppx->argv[ppx->count], ' ');
	if (ppx->count == 2)
	{
		dup2(pipefd[1], 1);
		dup2(ppx->fd1, 0);
		close (pipefd[0]);
		close (pipefd[1]);
	}
	else if (ppx->count == (ppx->argc - 2))
	{
		dup2(pipefd[0], 0);
		dup2(ppx->fd2, 1);
		close (pipefd[1]);
		close (pipefd[0]);
	}
	else
	{
		dup2(pipefd[1], 1);
		dup2(pipefd[0], 0);
	}
	ft_putstr_fd("here\n", 2);
	execve(findcmdpath(ppx), argv, ppx->envp);
	customexit("EXECVE");
}

void	parentprocess(int *pipefd, int pid)
{
	int	status;

	close (pipefd[1]);
	close (pipefd[0]);
	waitpid(pid, &status, 0);
}

int	forkprocess(t_ppx *ppx)
{
	int		pipefd[2];
	pid_t	pid;

	// ppx->pipefd = (initpipefd(ppx));
	pid = fork();
	if (pid == -1)
		customexit("FORK");
	else if (pid == 0)
		childprocess(ppx, pipefd);
	else
		parentprocess(pipefd, pid);
	return (0);
}
