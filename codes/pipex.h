/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:48:55 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/10 14:33:27 by ghwa             ###   ########.fr       */
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

typedef struct s_heredoc {
	char	*limiter;
	char	*input;
}	t_hd;

typedef struct s_ppx {
	int		argc;
	char	**argv;
	char	**envp;
	int		heredoc;
	char	*file1;
	char	*file2;
	int		fd1;
	int		fd2;
	int		**pipefdarray;
	int		pipefdcount;
	int		pid;
	int		pipecount;
	int		count;
	char	**envppath;
	int		bincount;
}	t_ppx;

int		initall(t_ppx *ppx, int argc, char **argv, char **envp);
int		forkprocess(t_ppx *ppx, t_hd *hd);
int		accesscheck(t_ppx *ppx, int argc, char **argv);
char	*findcmdpath(t_ppx *ppx);
int		customexit(char *string);
void	parentprocess(t_ppx *ppx);
void	freeall(t_ppx *ppx);
int		initheredoc(t_ppx *ppx, t_hd *hd);
char	*heredocinput(t_ppx *ppx, t_hd *hd);


#endif