/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:25:12 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/07 17:09:46 by ghwa             ###   ########.fr       */
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
     1	total 136
     2	-rw-r--r--   1 ghwa  2023_kuala-lumpur   1315 Nov  3 18:17 Makefile
     3	drwxr-xr-x  13 ghwa  2023_kuala-lumpur    442 Nov  7 17:17 codes
     4	-rwxr-xr-x   1 ghwa  2023_kuala-lumpur  55880 Nov  7 17:17 pipex
     5	-rw-r--r--@  1 ghwa  2023_kuala-lumpur   1159 Nov  7 17:09 test.c
     6	-rw-r--r--   1 ghwa  2023_kuala-lumpur    383 Nov  7 17:17 test2.c
heredocheredoccc