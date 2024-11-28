
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:08:43 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:09:08 by blucken          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_env(char *name, char **env)
{
	int		i;
	size_t	name_len;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}