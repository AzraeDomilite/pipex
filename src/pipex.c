/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:05:22 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 14:05:51 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parent(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	exec(av[3], env);
}

void	child(char **av, int *pipe_fd, char **env)
{
	int	fd;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	exec(av[2], env);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}
char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_putstr_fd("usage : ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child(av, pipe_fd, env);
	parent(av, pipe_fd, env);
}