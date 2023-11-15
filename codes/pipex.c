/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:25:12 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/15 10:51:00 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;
	t_hd	hd;

	if (initall(&ppx, argc, argv, envp) == 0)
		return (0);
	if (initheredoc(&ppx, &hd) == 0)
		return (0);
	printf("argc = %d\n", argc);
	printf("pipecount = %d\n", ppx.pipecount);
	printf("heredoc = %d\n", ppx.heredoc);
	printf("limiter = %s\n\n", hd.limiter);
	while (ppx.count < argc - 1)
	{
		forkprocess(&ppx, &hd);
		ppx.count++;
	}
	parentprocess(&ppx);
	// freeall(&ppx);
	return (0);
}
