/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:56:00 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:56:24 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <limits.h>
# include <sys/stat.h>

void	exit_handler(int n_exit);
int		open_file(char *file, int flags, mode_t mode);
void	ft_free_tab(char **tab);
char	*get_env(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	child(char **av, int *p_fd, char **env);
void	parent(char **av, int *p_fd, char **env);
void	error_exit(char *message, int exit_code);
void	close_pipes(int *fd);
char	**parse_command(const char *cmd);

#endif
