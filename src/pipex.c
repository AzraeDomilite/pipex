/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:02:21 by blucken           #+#    #+#             */
/*   Updated: 2024/12/04 17:02:43 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **argv, char **env, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
	{
		ft_putstr_fd("Error: ", 2);
		perror(argv[1]);
		exit(1);
	}
	if (dup2(filein, STDIN_FILENO) == -1)
		error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	close(fd[0]);
	close(fd[1]);
	close(filein);
	execute(argv[2], env);
}

void	parent_process(char **argv, char **env, int *fd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error();
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error();
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error();
	close(fd[0]);
	close(fd[1]);
	close(fileout);
	execute(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		return (1);
	}
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child_process(argv, env, fd);
	parent_process(argv, env, fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
