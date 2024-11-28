/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:06:52 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 13:15:32 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_pipex(int fd_exit)
{
	if (fd_exit == 1)
	{
		ft_putstr_fd("usage : ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	int		i;	
	int		fd_in;
	int		fd_out;

	if (ac != 5)
		exit_pipex(1);
	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		exit(EXIT_FAILURE);
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < 2)
	{
		if (fork() == 0)
		{
			if (i == 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			else
			{
				dup2(fd_out, 1);
				close(fd_out);
			}
			execve(av[i + 2], &av[i + 2], env);
		}
		i++;
	}
	exit(EXIT_SUCCESS);
}