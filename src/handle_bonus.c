/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:52:19 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 18:52:19 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/**
 * @brief Handle the heredoc input.
 * 
 * This function handles the heredoc input by reading lines from the standard input
 * until the limiter is encountered, and writes the lines to a temporary file.
 * 
 * @param data The pipex data structure.
 */
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

/**
 * @brief Handle the input for a command.
 * 
 * This function handles the input redirection for a command.
 * 
 * @param index The index of the command.
 * @param data The pipex data structure.
 */
void	handle_input(int index, t_pipex *data)
{
	int	in_fd;

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
	{
		dup2(data->pipes[index - 1][0], STDIN_FILENO);
	}
}

/**
 * @brief Handle the output for a command.
 * 
 * This function handles the output redirection for a command.
 * 
 * @param index The index of the command.
 * @param data The pipex data structure.
 */
void	handle_output(int index, t_pipex *data)
{
	int	out_fd;

	if (index == data->cmd_count - 1)
	{
		out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->is_heredoc)
			out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd == -1)
			error();
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	else
	{
		dup2(data->pipes[index][1], STDOUT_FILENO);
	}
}
