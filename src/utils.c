/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:40:13 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 18:50:44 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Get the paths from the environment variable.
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
 * @brief Print an error message for bad arguments and return the value.
 * 
 * @param value The value to return.
 * @return int The value.
 */
int	bad_args(int value)
{
	ft_putstr_fd("Error: Bad arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	return (value);
}
