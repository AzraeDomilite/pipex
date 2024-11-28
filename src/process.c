/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2028/11/20 21:02:49 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:03:30 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parent(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	redirect_io(fd, STDOUT_FILENO);
	redirect_io(pipe_fd[0], STDIN_FILENO);
	close_pipes(pipe_fd);
	close(fd);
	exec(av[3], env);
}

void	child(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open_file(av[1], O_RDONLY, 0);
	redirect_io(fd, STDIN_FILENO);
	redirect_io(pipe_fd[1], STDOUT_FILENO);
	close_pipes(pipe_fd);
	close(fd);
	exec(av[2], env);
}
