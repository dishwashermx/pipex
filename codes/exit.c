/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:37:44 by ghwa              #+#    #+#             */
/*   Updated: 2023/10/31 09:12:12 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	customexit(char *string)
{
	ft_putstr_fd("customexit\n", 2);
	perror(string);
	exit(EXIT_FAILURE);
	return (0);
}
