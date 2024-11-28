/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:03:25 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:24:48 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_exit(char *msg, int fd)
{
	perror(msg);
	exit(fd);
}

void	close_pipes(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	check_args(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	parent(char **av, int *pipe_fd, char **env)
{
	// ...existing code...
	exec(av[3], env);
}

void	child(char **av, int *pipe_fd, char **env)
{
	// ...existing code...
	exec(av[2], env);
}
