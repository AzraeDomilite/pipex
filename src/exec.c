/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:13:37 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:24:48 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_cmd_error(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		error_exit("split", 1);
	path = get_path(s_cmd[0], env);
	if (!path)
	{
		print_cmd_error(s_cmd[0]);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
	execve(path, s_cmd, env);
	free(path);
	ft_free_tab(s_cmd);
	error_exit("execve", 1);
}
