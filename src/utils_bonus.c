/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:01:03 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 18:52:24 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/**
 * @brief Get the paths from the environment variable.
 * 
 * This function searches for the PATH environment variable and splits it into an array of paths.
 * 
 * @param env The environment variables.
 * @return char** The paths split by ':'.
 */
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

/**
 * @brief Free the paths array and return the path.
 * 
 * This function frees the memory allocated for the paths array and returns the specified path.
 * 
 * @param path The path to return.
 * @param paths The paths array to free.
 * @return char* The path.
 */
char	*zero_access(char *path, char **paths)
{
	ft_free_array(paths);
	return (path);
}

/**
 * @brief Close all pipes and free the allocated memory.
 * 
 * This function closes all pipes and frees the memory allocated for the pipes array.
 * 
 * @param data The pipex data structure.
 */
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

/**
 * @brief Print an error message for bad arguments and return the value.
 * 
 * This function prints an error message for bad arguments and returns the specified value.
 * 
 * @param value The value to return.
 * @return int The value.
 */
int	bad_args(int value)
{
	ft_putstr_fd("Error: Bad arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <optional heredoc>", 2);
	ft_putstr_fd("<file1> <cmd1> ... <cmd_n> <file2>\n", 1);
	return (value);
}
