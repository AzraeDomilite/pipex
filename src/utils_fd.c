/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2028/11/20 21:02:47 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:03:29 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	redirect_io(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		error_exit("dup2", 1);
}

int	open_file(char *file, int flags, mode_t mode)
{
	int	fd;

	if (mode)
		fd = open(file, flags, mode);
	else
		fd = open(file, flags);
	if (fd == -1)
		error_exit("open", 1);
	return (fd);
}
