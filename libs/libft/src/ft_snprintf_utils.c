/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:43:08 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:43:09 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_snprintf.h"
#include "../include/libft.h"

size_t	handle_ptr(char *str, size_t size, void *value, t_format fmt)
{
	char	*addr_str;
	size_t	len;

	addr_str = ft_ptoa(value);
	if (!addr_str)
		return (0);
	len = handle_padding(str, size, addr_str, fmt);
	free(addr_str);
	return (len);
}

size_t	handle_string(char *str, size_t size, char *value, t_format fmt)
{
	size_t	len;

	if (!value)
		value = "(null)";
	len = handle_padding(str, size, value, fmt);
	return (len);
}

size_t	handle_char(char *str, size_t size, int value, t_format fmt)
{
	char		c;
	char		pad_char;
	t_padding	pad;

	pad.size = size;
	pad.pos = 0;
	c = (char)value;
	if (fmt.width > 1)
	{
		if (fmt.zero_pad)
			pad_char = '0';
		else
			pad_char = ' ';
		if (!fmt.left_align)
			pad.pos += write_padding(str, pad, pad_char, fmt.width - 1);
	}
	if (str && pad.pos < pad.size - 1)
		str[pad.pos] = c;
	pad.pos++;
	if (fmt.width > 1 && fmt.left_align)
		pad.pos += write_padding(str, pad, ' ', fmt.width - 1);
	return (pad.pos);
}

size_t	handle_float(char *str, size_t size, double value, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_ftoa(value, fmt.precision);
	if (!num_str)
		return (0);
	len = handle_padding(str, size, num_str, fmt);
	free(num_str);
	return (len);
}

size_t	handle_percent(char *str, size_t size, t_format fmt)
{
	t_padding	pad;
	char		pad_char;

	pad.size = size;
	pad.pos = 0;
	if (fmt.width > 1)
	{
		if (fmt.zero_pad)
			pad_char = '0';
		else
			pad_char = ' ';
		if (!fmt.left_align)
			pad.pos += write_padding(str, pad, pad_char, fmt.width - 1);
	}
	if (str && pad.pos < pad.size - 1)
		str[pad.pos] = '%';
	pad.pos++;
	if (fmt.width > 1 && fmt.left_align)
		pad.pos += write_padding(str, pad, ' ', fmt.width - 1);
	return (pad.pos);
}
