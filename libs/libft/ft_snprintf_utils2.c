/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:33:03 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:02:23 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"
#include "libft.h"

size_t	write_padding(char *str, size_t size, size_t pos, char pad_char, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && pos + i < size - 1 && str)
	{
		str[pos + i] = pad_char;
		i++;
	}
	return (i);
}

size_t	write_str(char *str, size_t size, size_t pos, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] && pos + i < size - 1 && str)
	{
		str[pos + i] = src[i];
		i++;
	}
	return (i);
}

size_t	handle_int(char *str, size_t size, int value, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_itoa(value);
	if (!num_str)
		return (0);
	len = handle_padding(str, size, num_str, fmt);
	free(num_str);
	return (len);
}

size_t	handle_uint(char *str, size_t size, unsigned int value, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_utoa(value);
	if (!num_str)
		return (0);
	len = handle_padding(str, size, num_str, fmt);
	free(num_str);
	return (len);
}

size_t	handle_hex(char *str, size_t size, unsigned int value, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_utoa_base(value, 16);
	if (!num_str)
		return (0);
	if (fmt.type == 'X')
		ft_strtoupper(num_str);
	len = handle_padding(str, size, num_str, fmt);
	free(num_str);
	return (len);
}