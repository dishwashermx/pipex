/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/03 15:14:56 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childprocess(t_ppx *ppx)
{
	char	**argv;

	if (ppx->count == 2)
	{
		close (ppx->pipefd[0]);
		ft_putstr_fd("child 1\n", 2);
		dup2(ppx->fd1, 0);
		dup2(ppx->pipefd[1], 1);
	}
	else if (ppx->count == (ppx->argc - 2))
	{
		close (ppx->pipefd[1]);
		ft_putstr_fd("child 2\n", 2);
		dup2(ppx->pipefd[0], 0);
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

void	parentprocess(t_ppx *ppx)
{
	int	status;

	printf("waiting for pid: %d\n", ppx->pid);
	close (ppx->pipefd[0]);
	close (ppx->pipefd[1]);
	waitpid(ppx->pid, &status, 0);
	if (WIFEXITED(status))
		ft_printf("Child process exited with status: %d\n", WEXITSTATUS(status));
	else
		ft_printf("Child process terminated abnormally\n");
}

int	forkprocess(t_ppx *ppx)
{
	pid_t	pid;

	printf("FD     1 %d\n", ppx->fd1);
	printf("FD     2 %d\n", ppx->fd2);
	printf("PIPEFD 0 %d\n", ppx->pipefd[0]);
	printf("PIPEFD 1 %d\n", ppx->pipefd[1]);
	pid = fork();
	if (ppx->count == (ppx->argc - 2))
		ppx->pid = pid;
	if (pid == -1)
		customexit("FORK");
	else if (pid == 0)
		childprocess(ppx);
	return (0);
}
