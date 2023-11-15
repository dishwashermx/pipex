/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/15 11:51:59 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*findcmdpath(t_ppx *ppx)
{
	int		c;
	char	*cmd;
	char	**splitty;

	c = 0;
	cmd = ft_strjoin("/", ppx->argv[ppx->count]);
	splitty = ft_split(cmd, ' ');
	while (c < ppx->bincount)
	{
		if (access(ft_strjoin(ppx->envppath[c], splitty[0]), X_OK) >= 0)
			return (ft_strjoin(ppx->envppath[c], splitty[0]));
		c++;
	}
	customexit("ERR_CMD");
	return (NULL);
}

int	accesscheck(t_ppx *ppx, int argc, char **argv)
{
	char	*file1;
	char	*file2;

	file2 = ft_strjoin("./", argv[argc - 1]);
	if (ppx->heredoc == 0)
	{
		file1 = ft_strjoin("./", argv[1]);
		ppx->fd1 = open(file1, O_RDONLY);
		if (ppx->fd1 < 0)
			return (customexit("ERR_INFILE"));
	}
	ppx->fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (ppx->fd2 < 0)
		return (customexit("ERR_OUTFILE"));
	if (argc < 5)
		return (customexit("ERROR: INSUFFICIENT ARGUMENTS"));
	return (1);
}

// void	freeall(t_ppx *ppx)
// {
// 	int	i;

// 	i = 0;
// 	ft_putstr_fd("test\n", 2);
// }
