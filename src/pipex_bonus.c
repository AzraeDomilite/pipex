/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:51:48 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 18:56:15 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/**
 * @brief Create pipes for the pipex program.
 * 
 * This function allocates memory for the pipes and creates the pipes using the 
 * `pipe` system call.
 * 
 * @param data The pipex data structure.
 */
void	create_pipes(t_pipex *data)
{
	int	i;

	data->pipes = malloc(sizeof(int *) * data->pipe_count);
	if (!data->pipes)
		error();
	i = 0;
	while (i < data->pipe_count)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			error();
		if (pipe(data->pipes[i]) == -1)
			error();
		i++;
	}
}

/**
 * @brief Execute a command.
 * 
 * This function handles the input and output redirection for a command,
 * closes all pipes, and executes the command.
 * 
 * @param index The index of the command.
 * @param argv The argument values.
 * @param env The environment variables.
 * @param data The pipex data structure.
 */
void	exec_cmd(int index, char **argv, char **env, t_pipex *data)
{
	handle_input(index, data);
	handle_output(index, data);
	close_pipes(data);
	execute(argv[index + 2 + data->is_heredoc], env);
}

/**
 * @brief The main function of the pipex bonus program.
 * 
 * This function sets up a pipeline between multiple commands using `pipe` and 
 * `fork`. It creates multiple pipes, forks child processes, and uses `dup2` to 
 * redirect input and output file descriptors.
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
 * - `unlink`: Deletes a name from the filesystem.
 */
int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	pid_t	*pid;

	if (argc < 5)
		return (bad_args(1));
	init_and_create_pipes(&data, argc, argv);
	pid = fork_and_exec_cmds(&data, argv, env);
	close_pipes(&data);
	wait_for_children(pid, data.cmd_count);
	free(pid);
	if (data.is_heredoc)
		unlink(".heredoc_tmp");
	return (0);
}
