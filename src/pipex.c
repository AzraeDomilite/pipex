/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:17:57 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 19:19:16 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* utils_process.c */
void	error_exit(char *msg, int fd)
{
	perror(msg);
	exit(fd);
}

void	close_pipes(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	check_args(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
}

/* utils_fd.c */
void	redirect_io(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		error_exit("dup2", 1);
}

int	open_file(char *file, int flags, mode_t mode)
{
	int	fd;

	if (mode)
		fd = open(file, flags, mode);
	else
		fd = open(file, flags);
	if (fd == -1)
		error_exit("open", 1);
	return (fd);
}

/* process.c */
void	parent(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	redirect_io(fd, STDOUT_FILENO);
	redirect_io(pipe_fd[0], STDIN_FILENO);
	close_pipes(pipe_fd);
	close(fd);
	exec(av[3], env);
}

void	child(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open_file(av[1], O_RDONLY, 0);
	redirect_io(fd, STDIN_FILENO);
	redirect_io(pipe_fd[1], STDOUT_FILENO);
	close_pipes(pipe_fd);
	close(fd);
	exec(av[2], env);
}

/* exec.c */
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

/* path.c */
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
	return (ft_strdup(cmd));
}

/* main.c */
int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	check_args(ac);
	if (pipe(pipe_fd) == -1)
		error_exit("pipe", 1);
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
		child(av, pipe_fd, env);
	parent(av, pipe_fd, env);
	waitpid(pid, &status, 0);
	return (EXIT_SUCCESS);
}