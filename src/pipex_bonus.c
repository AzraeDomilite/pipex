/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:00:51 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 18:42:31 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/**
 * @brief Create pipes for the pipex program.
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
 * @param argc The argument count.
 * @param argv The argument values.
 * @param env The environment variables.
 * @return int The exit status.
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
