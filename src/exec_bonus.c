/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:41:36 by blucken           #+#    #+#             */
/*   Updated: 2024/12/05 17:41:37 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	if (!env || !*env || access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_paths_from_env(env);
	if (!paths)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (zero_access(path, paths));
		free(path);
		i++;
	}
	ft_free_array(paths);
	return (ft_strdup(cmd));
}

void	error(void)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(errno);
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(errno);
}

void	execute(char *argv, char **env)
{
	char	**cmd;
	char	*path;
	int		saved_errno;

	cmd = parse_cmd_with_quotes(argv);
	if (!cmd || !cmd[0])
		cmd_not_found(argv);
	path = find_path(cmd[0], env);
	if (!path)
	{
		ft_free_array(cmd);
		cmd_not_found(cmd[0]);
	}
	if (execve(path, cmd, env) == -1)
	{
		saved_errno = errno;
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(path);
		ft_free_array(cmd);
		exit(saved_errno);
	}
}
