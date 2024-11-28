/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:03:32 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 18:55:17 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>


void	parent(char **av, int *pipe_fd, char **env);
void	child(char **av, int *pipe_fd, char **env);
void	exec(char *cmd, char **env);
char	*get_path(char *cmd, char **env);
char	*get_env(char *name, char **env);

#endif