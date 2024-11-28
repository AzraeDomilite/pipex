/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:03:13 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:03:32 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	check_args(ac);
	if (pipe(pipe_fd) == -1)
		error_exit("pipe", 1);
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
		child(av, pipe_fd, env);
	parent(av, pipe_fd, env);
	waitpid(pid, &status, 0);
	return (EXIT_SUCCESS);
}
