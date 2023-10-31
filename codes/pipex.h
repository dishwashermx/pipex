/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:48:55 by ghwa              #+#    #+#             */
/*   Updated: 2023/10/31 10:42:41 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../../libft/libft.h"

typedef struct s_ppx {
	int		argc;
	char	**argv;
	char	**envp;
	int		heredoc;
	char	*file1;
	char	*file2;
	int		fd1;
	int		fd2;
	int		**pipefd;
	int		pipecount;
	int		count;
	char	**envppath;
	int		bincount;
}	t_ppx;

int		initall(t_ppx *ppx, int argc, char **argv, char **envp);
int		forkprocess(t_ppx *ppx);
int		accesscheck(t_ppx *ppx, int argc, char **argv);
char	*findcmdpath(t_ppx *ppx);
int		customexit(char *string);

#endif