/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/10/31 10:42:05 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*findcmdpath(t_ppx *ppx)
{
	int		c;
	char	*cmd;

	c = 0;
	cmd = ft_strjoin("/", ppx->argv[ppx->count]);
	while (c < ppx->bincount)
	{
		if (access(ft_strjoin(ppx->envppath[c], cmd), X_OK) >= 0)
			return (ft_strjoin(ppx->envppath[c], cmd));
		c++;
	}
	customexit("ERR_CMD");
	return (NULL);
}

int	accesscheck(t_ppx *ppx, int argc, char **argv)
{
	char	*file1;
	char	*file2;

	file1 = ft_strjoin("./", argv[1 + ppx->heredoc]);
	file2 = ft_strjoin("./", argv[argc - 1]);
	ppx->fd1 = open(file1, O_RDONLY);
	if (ppx->fd1 < 0)
		return (customexit("ERR_INFILE"));
	ppx->fd2 = open(file2, O_WRONLY | O_CREAT);
	if (ppx->fd2 < 0)
		return (customexit("ERR_OUTFILE"));
	return (1);
}