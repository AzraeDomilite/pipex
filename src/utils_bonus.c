/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:01:03 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 18:01:06 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	**get_paths_from_env(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*zero_access(char *path, char **paths)
{
	ft_free_array(paths);
	return (path);
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

int	bad_args(int value)
{
	ft_putstr_fd("Error: Bad arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <optional heredoc>", 2);
	ft_putstr_fd("<file1> <cmd1> ... <cmd_n> <file2>\n", 1);
	return (value);
}
