/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:27:16 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:27:39 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static size_t	arg_count(const char *str)
{
	size_t	count;
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && (quote || !ft_isspace(str[i])))
			{
				if (str[i] == '\'' || str[i] == '\"')
				{
					if (quote == '\0')
						quote = str[i];
					else if (quote == str[i])
						quote = '\0';
				}
				i++;
			}
		}
	}
	return (count);
}

static char	*get_next_arg(const char **str_ptr)
{
	const char	*str = *str_ptr;
	size_t		start;
	size_t		len = 0;
	char		quote = '\0';

	while (str[len] && ft_isspace(str[len]))
		len++;
	start = len;
	while (str[len] && (quote || !ft_isspace(str[len])))
	{
		if ((str[len] == '\'' || str[len] == '\"') \
			&& (quote == '\0' || quote == str[len]))
			quote = quote == '\0' ? str[len] : '\0';
		len++;
	}
	*str_ptr += len;
	return (ft_substr(str, start, len - start));
}

char	**parse_command(const char *cmd)
{
	size_t		count;
	char		**args;
	size_t		i;
	const char	*ptr;

	args = NULL;
	count = arg_count(cmd);
	*args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	ptr = cmd;
	while (i < count)
	{
		args[i] = get_next_arg(&ptr);
		i++;
	}
	args[i] = NULL;
	return (args);
}