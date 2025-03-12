/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:24:20 by blucken           #+#    #+#             */
/*   Updated: 2025/03/12 15:24:20 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libs/libft/include/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	int		count;
	int		in_quote;
	char	quote_char;
}			t_args;

typedef struct s_parse
{
	int		arg_count;
	char	**args;
	int		i;
	char	*tmp;
}			t_parse;

void	child_process(char **argv, char **env, int *fd);
void	parent_process(char **argv, char **env, int *fd);
void	error(void);
void	cmd_not_found(char *cmd);
void	execute(char *argv, char **env);
char	*find_path(char *cmd, char **env);
char	**parse_cmd_with_quotes(char *cmd);
void	ft_free_array(char **arr);
int		count_args(char *s);
char	**get_paths_from_env(char **env);
char	*zero_access(char *path, char **paths);
int		bad_args(int value);

#endif
