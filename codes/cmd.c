/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:34:17 by ghwa              #+#    #+#             */
/*   Updated: 2023/10/31 16:59:33 by ghwa             ###   ########.fr       */
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
