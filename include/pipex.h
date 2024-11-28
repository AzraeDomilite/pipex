/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:09:45 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:24:48 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <limits.h>
// #include <linux/limits.h>

/* Process functions */
void	parent(char **av, int *pipe_fd, char **env);
void	child(char **av, int *pipe_fd, char **env);
void	error_exit(char *msg, int fd);
void	close_pipes(int *pipe_fd);
void	check_args(int ac);

/* File descriptor functions */
void	redirect_io(int oldfd, int newfd);
int		open_file(char *file, int flags, mode_t mode);

/* Command execution functions */
void	exec(char *cmd, char **env);
void	print_cmd_error(char *cmd);

/* Path handling functions */
char	*get_path(char *cmd, char **env);
char	*check_direct_path(char *cmd);
char	*search_in_path(char *cmd, char **paths);
char	*get_env(char *name, char **env);

/* Utils functions */
char	**ft_split(char const *s, char c);
void	ft_free_tab(char **tab);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_snprintf(char *str, size_t size, const char *format, ...);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);

#endif
