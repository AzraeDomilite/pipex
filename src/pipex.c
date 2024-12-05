/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:50:44 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 18:56:14 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Handle the child process.
 * 
 * This function handles the child process by opening the input file,
 * redirecting the input and output file descriptors, and executing the command.
 * 
 * @param argv The argument values.
 * @param env The environment variables.
 * @param fd The file descriptors.
 */
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

/**
 * @brief Handle the parent process.
 * 
 * This function handles the parent process by opening the output file,
 * redirecting the input and output file descriptors, and executing the command.
 * 
 * @param argv The argument values.
 * @param env The environment variables.
 * @param fd The file descriptors.
 */
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

/**
 * @brief The main function of the pipex program.
 * 
 * This function sets up a pipeline between two commands using `pipe` and `fork`.
 * It creates a pipe, forks a child process, and uses `dup2` to redirect input
 * and output file descriptors.
 * 
 * @param argc The argument count.
 * @param argv The argument values.
 * @param env The environment variables.
 * @return int The exit status.
 * 
 * @details
 * - `fork`: Creates a new process by duplicating the calling process.
 * - `access`: Checks the file accessibility.
 * - `pipe`: Creates a unidirectional data channel that can be used for 
 *   interprocess communication.
 * - `dup`: Duplicates a file descriptor.
 * - `dup2`: Duplicates a file descriptor to a specified file descriptor.
 * - `execve`: Executes a program, replacing the current process image with a 
 *   new one.
 */
int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
		return (bad_args(1));
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
