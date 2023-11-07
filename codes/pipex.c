/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:25:12 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/07 17:01:34 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;

	if (initall(&ppx, argc, argv, envp) == 0)
		return (0);
	while (ppx.count < (argc - 1))
	{
		forkprocess(&ppx);
		ppx.count++;
	}
	parentprocess(&ppx);
	// freeall(&ppx);
	return (0);
}
