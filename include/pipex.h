/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:23:02 by blucken           #+#    #+#             */
/*   Updated: 2024/12/04 17:23:04 by blucken          ###   ########.fr       */
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
#endif
