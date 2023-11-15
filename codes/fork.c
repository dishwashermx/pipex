/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/15 11:39:00 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dupandclose(t_ppx *ppx)
{
	if (ppx->count == 2)
	{
		close (ppx->pipefdarray[ppx->pipefdcount][0]);
		dup2(ppx->pipefdarray[ppx->pipefdcount][1], 1);
		dup2(ppx->fd1, 0);
	}
	else if (ppx->count == (ppx->argc - 2))
	{
		close (ppx->pipefdarray[ppx->pipefdcount][1]);
		dup2(ppx->pipefdarray[ppx->pipefdcount][0], 0);
		dup2(ppx->fd2, 1);
	}
	else
	{
		close (ppx->pipefdarray[ppx->pipefdcount + 1][0]);
		close (ppx->pipefdarray[ppx->pipefdcount][1]);
		dup2(ppx->pipefdarray[ppx->pipefdcount][0], 0);
		dup2(ppx->pipefdarray[ppx->pipefdcount + 1][1], 1);
	}
}

void	closeallpipes(t_ppx *ppx, int code)
{
	int	i;

	i = 0;
	while (i < ppx->pipecount - ppx->heredoc && ppx->pipecount > 0)
	{
		if (code == 1)
		{
			close (ppx->pipefdarray[i][1]);
			close (ppx->pipefdarray[i][0]);
		}
		else if ((i == ppx->pipefdcount + 1) && \
		(ppx->count != (ppx->argc - 2)) && (ppx->count != 2))
			;
		else if ((i != ppx->pipefdcount) && (i < ppx->pipecount))
		{
			close (ppx->pipefdarray[i][1]);
			close (ppx->pipefdarray[i][0]);
		}
		i++;
	}
}

void	childprocess(t_ppx *ppx, t_hd *hd)
{
	char	**splitty;

	if (ppx->heredoc == 1 && ppx->count == 2)
	{
		closeallpipes(ppx, 0);
		heredocinput(ppx, hd);
		exit(EXIT_SUCCESS);
	}
	closeallpipes(ppx, 0);
	dupandclose(ppx);
	splitty = ft_split(ppx->argv[ppx->count], ' ');
	execve(findcmdpath(ppx), splitty, ppx->envp);
	customexit("EXECVE");
}

void	parentprocess(t_ppx *ppx)
{
	int	i;

	i = 0;
	closeallpipes(ppx, 1);
	while (i < ppx->pipecount)
	{
		wait(NULL);
		i++;
	}
}

int	forkprocess(t_ppx *ppx, t_hd *hd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		customexit("FORK");
	else if (pid == 0)
		childprocess(ppx, hd);
	if ((ppx->count > 2) && ppx->pipecount > 1)
		ppx->pipefdcount++;
	return (0);
}
