/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:30 by ghwa              #+#    #+#             */
/*   Updated: 2023/10/31 16:49:46 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	accesscheck(t_ppx *ppx, int argc, char **argv)
{
	char	*file1;
	char	*file2;

	file1 = ft_strjoin("./", argv[1 + ppx->heredoc]);
	file2 = ft_strjoin("./", argv[argc - 1]);
	// (void) argc;
	// file2 = "outfile.c";
	ppx->fd1 = open(file1, O_RDONLY);
	if (ppx->fd1 < 0)
		return (customexit("ERR_INFILE"));
	ppx->fd2 = open(file2, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (ppx->fd2 < 0)
		return (customexit("ERR_OUTFILE"));
	return (1);
}
