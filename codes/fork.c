/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/03 18:22:56 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dupandclose(t_ppx *ppx)
{
	if (ppx->count == 2)
	{
		close (ppx->pipefdarray[ppx->pipefdcount][0]);
		dup2(ppx->fd1, 0);
		dup2(ppx->pipefdarray[ppx->pipefdcount][1], 1);
	}
	else if (ppx->count == (ppx->argc - 2))
	{
		close (ppx->pipefdarray[ppx->pipefdcount][1]);
		dup2(ppx->pipefdarray[ppx->pipefdcount][0], 0);
		dup2(ppx->fd2, 1);
	}
	else
	{
		close (ppx->pipefdarray[ppx->pipefdcount][1]);
		dup2(ppx->pipefdarray[ppx->pipefdcount + 1][1], 1);
		dup2(ppx->pipefdarray[ppx->pipefdcount][0], 0);
	}
}

void	childprocess(t_ppx *ppx)
{
	int		i;

	i = 0;
	dupandclose(ppx);
	while (i < ppx->pipecount && ppx->pipecount > 1)
	{
		if (i == ppx->pipefdcount + 1)
			close (ppx->pipefdarray[i + 1][0]);
		else if (!(i == ppx->pipefdcount))
		{
			close (ppx->pipefdarray[i][1]);
			close (ppx->pipefdarray[i][0]);
		}
	}
	ppx->isplitthisinchild = ft_split(ppx->argv[ppx->count], ' ');
	execve(findcmdpath(ppx), ppx->isplitthisinchild, ppx->envp);
	customexit("EXECVE");
}

void	parentprocess(t_ppx *ppx)
{
	int	status;

	printf("waiting for pid: %d\n", ppx->pid);
	close (ppx->pipefdarray[ppx->pipefdcount][0]);
	close (ppx->pipefdarray[ppx->pipefdcount][1]);
	waitpid(ppx->pid, &status, 0);
	if (WIFEXITED(status))
		ft_printf("Child process exited with status: %d\n", WEXITSTATUS(status));
	else
		ft_printf("Child process terminated abnormally\n");
}

int	forkprocess(t_ppx *ppx)
{
	pid_t	pid;

	pid = fork();
	if (ppx->count == 2)
		ppx->pipefdcount = 0;
	else if (ppx->count == (ppx->argc - 2))
		ppx->pid = pid;
	if (ppx->count > 3)
		close(ppx->pipefdarray[ppx->pipefdcount - 1][0]);
	if (pid == -1)
		customexit("FORK");
	else if (pid == 0)
		childprocess(ppx);
	if (ppx->count > 2 && ppx->pipecount > 1)
		ppx->pipefdcount++;
	return (0);
}
