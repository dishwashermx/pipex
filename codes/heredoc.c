/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:04:12 by ghwa              #+#    #+#             */
/*   Updated: 2023/11/15 11:39:23 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	initheredoc(t_ppx *ppx, t_hd *hd)
{
	if (ppx->heredoc == 0)
		return (1);
	hd->limiter = ppx->argv[2];
	hd->input = NULL;
	return (1);
}

char	*heredocinput(t_ppx *ppx, t_hd *hd)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	ft_putstr_fd("here_doc > ", 2);
	close (ppx->pipefdarray[ppx->pipefdcount][0]);
	while (1)
	{
		temp = get_next_line(0);
		if (ft_strncmp(hd->limiter, temp, ft_strlen(hd->limiter)) == 0)
		{
			dup2(ppx->pipefdarray[ppx->pipefdcount][1], 1);
			free (hd->input);
			free (temp);
			return (NULL);
		}
		if (hd->input == NULL)
			hd->input = ft_strdup(temp);
		else
			hd->input = ft_strjoin(hd->input, temp);
		free (temp);
		ft_putstr_fd("here_doc > ", 2);
	}
	return (0);
}
