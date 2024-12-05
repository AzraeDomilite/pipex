/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:22:46 by blucken           #+#    #+#             */
/*   Updated: 2024/12/04 17:22:54 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "../libs/libft/include/libft.h"

typedef struct s_pipex
{
	int		pipe_count;
	int		**pipes;
	int		cmd_count;
	int		is_heredoc;
	char	*limiter;
	char	*infile;
	char	*outfile;
}			t_pipex;

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

void	cmd_not_found(char *cmd);
void	error(void);
void	execute(char *argv, char **env);
char	**parse_cmd_with_quotes(char *cmd);
void	create_pipes(t_pipex *data);
void	close_pipes(t_pipex *data);
void	handle_heredoc(t_pipex *data);
void	init_pipex(t_pipex *data, int argc, char **argv);
void	exec_cmd(int index, char **argv, char **env, t_pipex *data);
int		count_args(char *s);
#endif
