/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/03 10:26:49 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childprocess(t_ppx *ppx, int *pipefd)
{
	char	**argv;

	if (ppx->count == 2)
	{
		close (pipefd[0]);
		ft_putstr_fd("child 1\n", 2);
		dup2(pipefd[1], 1);
		dup2(ppx->fd1, 0);
	}
	else if (ppx->count == (ppx->argc - 2))
	{
		close (pipefd[1]);
		ft_putstr_fd("child 2\n", 2);
		dup2(pipefd[0], 0);
		dup2(ppx->fd2, 1);
	}
	// else
	// {
	// 	dup2(pipefd[1], 1);
	// 	dup2(pipefd[0], 0);
	// }
	argv = ft_split(ppx->argv[ppx->count], ' ');
	execve(findcmdpath(ppx), argv, ppx->envp);
	customexit("EXECVE");
}

void	parentprocess(t_ppx *ppx, int *pipefd, int pid)
{
	int	status;

	close (pipefd[1]);
	close (pipefd[0]);
	printf("%d pid\n", pid);
	if (waitpid(pid, &status, 0) == -1)
		customexit("WAITPID");
	if (WIFEXITED(status))
		ft_printf("Child process %d exited with status: %d\n", ppx->count, WEXITSTATUS(status));
	else
		ft_printf("Child process %d terminated abnormally\n", ppx->count);
}

int	forkprocess(t_ppx *ppx)
{
	int		pipefd[2];
	pid_t	pid;

	// ppx->pipefd = (initpipefd(ppx));
	if (pipe(pipefd) < 0)
		customexit("PIPE");
	printf("FD     1 %d\n", ppx->fd1);
	printf("FD     2 %d\n", ppx->fd2);
	printf("PIPEFD 0 %d\n", pipefd[0]);
	printf("PIPEFD 1 %d\n", pipefd[1]);
	pid = fork();
	if (pid == -1)
		customexit("FORK");
	else if (pid == 0)
		childprocess(ppx, pipefd);
	else
		parentprocess(ppx, pipefd, pid);
	return (0);
}
