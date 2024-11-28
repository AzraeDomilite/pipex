/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:07:25 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:24:48 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


char	*check_direct_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

char	*search_in_path(char *cmd, char **paths)
{
	char	*exec;
	char	path_part[PATH_MAX];
	int		i;

	i = -1;
	exec = NULL;
	while (paths[++i])
	{
		ft_snprintf(path_part, PATH_MAX, "%s/%s", paths[i], cmd);
		if (access(path_part, F_OK | X_OK) == 0)
		{
			exec = ft_strdup(path_part);
			break ;
		}
	}
	return (exec);
}

char	*get_path(char *cmd, char **env)
{
	char	**allpath;
	char	*exec;

	if (!cmd || !env)
		return (NULL);
	exec = check_direct_path(cmd);
	if (exec)
		return (exec);
	allpath = ft_split(get_env("PATH", env), ':');
	if (!allpath)
		return (NULL);
	exec = search_in_path(cmd, allpath);
	ft_free_tab(allpath);
	if (exec)
		return (exec);
	return (NULL);
}
