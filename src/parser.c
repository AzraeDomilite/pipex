/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:25:50 by blucken           #+#    #+#             */
/*   Updated: 2024/12/04 17:26:21 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_args	set_args(void)
{
	t_args	args;

	args.count = 0;
	args.in_quote = 0;
	args.quote_char = 0;
	return (args);
}

int	count_args(char *s)
{
	int		count;
	int		in_quote;
	char	quote_char;

	count = 0;
	in_quote = 0;
	quote_char = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			if (!in_quote)
			{
				in_quote = 1;
				quote_char = *s;
			}
			else if (*s == quote_char)
				in_quote = 0;
		}
		else if ((*s == ' ' || *s == '\t') && !in_quote)
		{
			while (*(s + 1) == ' ' || *(s + 1) == '\t')
				s++;
			count++;
		}
		s++;
	}
	return (count + 1);
}

static char	*extract_quoted(char **str)
{
	char	*start;
	char	*result;
	int		len;
	char	quote;

	quote = *(*str - 1);
	start = *str;
	len = 0;
	while ((*str)[len] && (*str)[len] != quote)
		len++;
	result = ft_substr(start, 0, len);
	*str += len + ((*str)[len] == quote);
	return (result);
}

static char	*extract_unquoted(char **str)
{
	char	*start;
	int		len;

	start = *str;
	len = 0;
	while ((*str)[len] && (*str)[len] != ' ' && (*str)[len] != '\t'
		&& (*str)[len] != '"' && (*str)[len] != '\'')
		len++;
	*str += len;
	return (ft_substr(start, 0, len));
}

char	**parse_cmd_with_quotes(char *cmd)
{
	t_parse	parse;

	parse.arg_count = count_args(cmd);
	parse.args = malloc(sizeof(char *) * (parse.arg_count + 1));
	if (!parse.args)
		return (NULL);
	parse.i = 0;
	while (*cmd)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		if (!*cmd)
			break ;
		if (*cmd == '"' || *cmd == '\'')
			parse.tmp = extract_quoted(&cmd);
		else
			parse.tmp = extract_unquoted(&cmd);
		if (parse.tmp && *parse.tmp)
			parse.args[parse.i++] = parse.tmp;
		else
			free(parse.tmp);
	}
	parse.args[parse.i] = NULL;
	return (parse.args);
}
