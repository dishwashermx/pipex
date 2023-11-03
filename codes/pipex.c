/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:25:12 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/03 15:07:03 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;

	if (initall(&ppx, argc, argv, envp) == 0)
		return (0);
	if (pipe(ppx.pipefd) < 0)
		customexit("PIPE");
	while (ppx.count < (argc - 1))
	{
		forkprocess(&ppx);
		ppx.count++;
	}
	parentprocess(&ppx);
}
