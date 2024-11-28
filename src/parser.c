
#include "../include/pipex.h"

static size_t	arg_count(const char *str)
{
	size_t	count = 0;
	size_t	i = 0;
	char	quote = '\0';

	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && (quote || !ft_isspace(str[i])))
			{
				if ((str[i] == '\'' || str[i] == '\"') && (quote == '\0' || quote == str[i]))
					quote = quote == '\0' ? str[i] : '\0';
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
		if ((str[len] == '\'' || str[len] == '\"') && (quote == '\0' || quote == str[len]))
			quote = quote == '\0' ? str[len] : '\0';
		len++;
	}
	*str_ptr += len;
	return (ft_substr(str, start, len - start));
}

char	**parse_command(const char *cmd)
{
	size_t	count = arg_count(cmd);
	char	**args = malloc(sizeof(char *) * (count + 1));
	size_t	i = 0;
	const char	*ptr = cmd;

	if (!args)
		return (NULL);
	while (i < count)
	{
		args[i] = get_next_arg(&ptr);
		i++;
	}
	args[i] = NULL;
	return (args);
}