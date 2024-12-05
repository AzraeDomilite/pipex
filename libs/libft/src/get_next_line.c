/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:42:37 by blucken           #+#    #+#             */
/*   Updated: 2024/12/04 16:43:04 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"
#include "../include/libft.h"

char	*ft_next(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_calloc((ft_strlen(stash) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	free(stash);
	return (new_stash);
}

char	*ft_line(char *stash)
{
	char	*line;
	int		i;
	int		n;

	i = 0;
	n = 1;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		n++;
	line = ft_calloc(i + n, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_join_buffer_stash(char *stash, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buffer);
	free(stash);
	return (tmp);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	int		byte_read;

	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[byte_read] = 0;
		stash = ft_join_buffer_stash(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_line(stash);
	stash = ft_next(stash);
	return (line);
}
