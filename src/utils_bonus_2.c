/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:56:25 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 17:56:29 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_and_create_pipes(t_pipex *data, int argc, char **argv)
{
	init_pipex(data, argc, argv);
	create_pipes(data);
}

pid_t	*fork_and_exec_cmds(t_pipex *data, char **argv, char **env)
{
	pid_t	*pid;
	int		i;

	pid = malloc(sizeof(pid_t) * data->cmd_count);
	if (!pid)
		error();
	i = 0;
	while (i < data->cmd_count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error();
		if (pid[i] == 0)
			exec_cmd(i, argv, env, data);
		i++;
	}
	return (pid);
}

void	wait_for_children(pid_t *pid, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	while (i++ < cmd_count)
		waitpid(pid[i - 1], &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(1);
}

void	init_pipex(t_pipex *data, int argc, char **argv)
{
	data->is_heredoc = !ft_strcmp(argv[1], "here_doc");
	if (data->is_heredoc)
	{
		if (argc < 6)
		{
			ft_putstr_fd("Error: Not enough arguments for heredoc\n", 2);
			exit(1);
		}
		data->limiter = argv[2];
		data->cmd_count = argc - 4;
		data->outfile = argv[argc - 1];
		handle_heredoc(data);
	}
	else
	{
		data->infile = argv[1];
		data->outfile = argv[argc - 1];
		data->cmd_count = argc - 3;
	}
	data->pipe_count = data->cmd_count - 1;
}
