/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:43:19 by blucken           #+#    #+#             */
/*   Updated: 2024/12/04 16:43:20 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

char	*ft_join_buffer_stash(char *stash, char *buffer);
char	*ft_next(char *buffer);
char	*ft_line(char *buffer);
char	*read_file(int fd, char *res);
char	*get_next_line(int fd);

#endif
