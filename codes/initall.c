/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:55:54 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/03 09:52:37 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initvalues(t_ppx *ppx, int argc, char **argv)
{
	char	*heredoc;

	heredoc = ft_strdup(argv[1]);
	if (ft_strncmp(heredoc, "here_doc", 9) == 0)
		ppx->heredoc = 1;
	else
		ppx->heredoc = 0;
	if (ppx->heredoc == 0)
		ppx->file1 = argv[0];
	else
		ppx->file1 = argv[1];
	ppx->file2 = argv[argc - 1];
	ppx->count = 2;
	ppx->argc = argc;
	ppx->argv = argv;
	free (heredoc);
}

int	initenvp(t_ppx *ppx, char **envp)
{
	int		c;
	char	*path;

	c = 0;
	ppx->envp = envp;
	while (envp[c])
	{
		if ((ft_strncmp(envp[c], "PATH=", 5)) == 0)
		{
			path = ft_substr(envp[c], 5, (ft_strlen(envp[c])));
			ppx->envppath = ft_split(path, ':');
			c = 0;
			while (ppx->envppath[c])
				c++;
			ppx->bincount = c;
			return (1);
		}
		c++;
	}
	return (0);
}

int	initall(t_ppx *ppx, int argc, char **argv, char **envp)
{
	initvalues(ppx, argc, argv);
	if (accesscheck(ppx, argc, argv) == 0)
		return (0);
	if (initenvp(ppx, envp) == 0)
		return (0);
	return (1);
}

// initpipefd(t_ppx *ppx)
// {
	
// }