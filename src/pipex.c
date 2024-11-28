/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:09:09 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 22:22:26 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = parse_command(cmd);
	path = get_path(args[0], env);
	if (path == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		ft_free_tab(args);
		exit(EXIT_FAILURE);
	}
	if (execve(path, args, env) == -1)
	{
		perror("Error");
		ft_putstr_fd("pipex: execution failed: ", 2);
		ft_putendl_fd(args[0], 2);
		ft_free_tab(args);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], O_RDONLY, 0);
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close_pipes(p_fd);
	close(fd);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	close_pipes(p_fd);
	close(fd);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		error_exit("usage: ./pipex file1 cmd1 cmd2 file2", 1);
	if (pipe(p_fd) == -1)
		error_exit("pipe", 1);
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		error_exit("fork", 1);
	}
	if (pid == 0)
		child(av, p_fd, env);
	parent(av, p_fd, env);
	if (waitpid(pid, NULL, 0) == -1)
		error_exit("waitpid", 1);
	return (EXIT_SUCCESS);
}
