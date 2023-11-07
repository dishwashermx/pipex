/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/07 17:01:41 by ghwa             ###   ########.fr       */
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
		close (ppx->pipefdarray[ppx->pipefdcount + 1][0]);
		dup2(ppx->pipefdarray[ppx->pipefdcount + 1][1], 1);
		dup2(ppx->pipefdarray[ppx->pipefdcount][0], 0);
	}
}

void	closeallpipes(t_ppx *ppx, int code)
{
	int	i;

	i = 0;
	while (i < ppx->pipecount && ppx->pipecount > 1)
	{
		if (code == 1)
		{
			close (ppx->pipefdarray[i][1]);
			close (ppx->pipefdarray[i][0]);
		}
		else if (i == ppx->pipefdcount + 1 && code == 0)
			;
		else if (!(i == ppx->pipefdcount) && (i < ppx->pipecount))
		{
			close (ppx->pipefdarray[i][1]);
			close (ppx->pipefdarray[i][0]);
		}
		else
			break ;
		i++;
	}
}

void	childprocess(t_ppx *ppx)
{
	char	**splitty;

	dupandclose(ppx);
	closeallpipes(ppx, 0);
	splitty = ft_split(ppx->argv[ppx->count], ' ');
	execve(findcmdpath(ppx), splitty, ppx->envp);
	customexit("EXECVE");
}

void	parentprocess(t_ppx *ppx)
{
	int	status;

	closeallpipes(ppx, 1);
	waitpid(-1, &status, 0);
	printf("waiting for %d\n", ppx->pid);
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
