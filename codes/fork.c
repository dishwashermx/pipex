/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/10/31 17:27:48 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childprocess(t_ppx *ppx, int *pipefd)
{
	char	**argv;

	argv = ft_split(ppx->argv[ppx->count], ' ');
	if (ppx->count == 2)
	{
		ft_putstr_fd("child 1\n", 2);
		ft_putnbr_fd(pipefd[1], 2);
		dup2(pipefd[1], 1);
		dup2(ppx->fd1, 0);
		close (pipefd[0]);
	}
	else if (ppx->count == (ppx->argc - 2))
	{
		ft_putnbr_fd(pipefd[0], 2);
		ft_putstr_fd("child 2\n", 2);
		dup2(pipefd[0], 0);
		dup2(ppx->fd2, 1);
		close (pipefd[1]);
	}
	// else
	// {
	// 	dup2(pipefd[1], 1);
	// 	dup2(pipefd[0], 0);
	// }
	ft_putstr_fd("before execve\n", 2);
	ft_putstr_fd(findcmdpath(ppx), 2);
	execve(findcmdpath(ppx), argv, ppx->envp);
	customexit("EXECVE");
}

void	parentprocess(int *pipefd, int pid)
{
	int	status;

	close (pipefd[1]);
	close (pipefd[0]);
	printf("%d pid\n", pid);
	if (waitpid(pid, &status, 0) == -1)
		customexit("WAITPID");
	if (WIFEXITED(status))
		ft_printf("Child process exited with status: %d\n", WEXITSTATUS(status));
	else
		ft_printf("Child process terminated abnormally\n");
}

int	forkprocess(t_ppx *ppx)
{
	int		pipefd[2];
	pid_t	pid;

	// ppx->pipefd = (initpipefd(ppx));
	if (pipe(pipefd) < 0)
		customexit("PIPE");
	pid = fork();
	if (pid == -1)
		customexit("FORK");
	else if (pid == 0)
		childprocess(ppx, pipefd);
	else
		parentprocess(pipefd, pid);
	return (0);
}
