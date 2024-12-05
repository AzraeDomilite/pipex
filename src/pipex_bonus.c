/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:11:11 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 12:11:34 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void	close_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
}

void	handle_heredoc(t_pipex *data)
{
	char	*line;
	int		temp_fd;

	temp_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd == -1)
		error();
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, data->limiter, ft_strlen(data->limiter))
			&& line[ft_strlen(data->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, temp_fd);
		free(line);
	}
	close(temp_fd);
	data->infile = ".heredoc_tmp";
}

void	exec_cmd(int index, char **argv, char **env, t_pipex *data)
{
	int	in_fd;
	int	out_fd;

	if (index == 0)
	{
		in_fd = open(data->infile, O_RDONLY);
		if (in_fd == -1)
		{
			if (data->is_heredoc)
				unlink(".heredoc_tmp");
			error();
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else
		dup2(data->pipes[index - 1][0], STDIN_FILENO);
	if (index == data->cmd_count - 1)
	{
		out_fd = open(data->outfile, O_WRONLY | O_CREAT, 0644);
		if (data->is_heredoc)
		{
			out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (out_fd == -1)
		{
			error();
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	else
		dup2(data->pipes[index][1], STDOUT_FILENO);
	close_pipes(data);
	execute(argv[index + 2 + data->is_heredoc], env);
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

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	pid_t	*pid;
	int		i;
	int		status;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Not enough arguments\n", 2);
		return (1);
	}
	init_pipex(&data, argc, argv);
	create_pipes(&data);
	pid = malloc(sizeof(pid_t) * data.cmd_count);
	if (!pid)
		error();
	i = 0;
	while (i < data.cmd_count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error();
		if (pid[i] == 0)
			exec_cmd(i, argv, env, &data);
		i++;
	}
	close_pipes(&data);
	i = 0;
	while (i < data.cmd_count)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
	if (data.is_heredoc)
		unlink(".heredoc_tmp");
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
