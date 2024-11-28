/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:22:59 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 20:23:02 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"
#include "libft.h"

size_t	handle_input(char *str, size_t size, const char *format, va_list args)
{
	size_t		count;
	const char	*ptr;

	count = 0;
	ptr = format;
	while (*ptr)
	{
		if (*ptr == '%' && *(ptr + 1))
		{
			ptr++;
			count += handle_format(str, size, &ptr, args);
		}
		else
		{
			if (str && count < size - 1)
				str[count] = *ptr;
			count++;
			ptr++;
		}
	}
	if (str && size > 0)
	{
		if (count < size)
			str[count] = '\0';
		else
			str[size - 1] = '\0';
	}
	return (count);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	size_t	count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = handle_input(str, size, format, args);
	va_end(args);
	return ((int)count);
}

t_format	parse_format(const char **format)
{
	t_format	fmt;
	const char	*ptr;

	ft_memset(&fmt, 0, sizeof(fmt));
	ptr = *format;
	while (*ptr)
	{
		if (ft_strchr("-+ #0", *ptr))
			set_flags(&fmt, *ptr);
		else if (ft_isdigit(*ptr) || *ptr == '.')
			parse_width_precision(&fmt, &ptr);
		else if (ft_strchr("diuxXpscf%", *ptr))
		{
			fmt.type = *ptr;
			*format = ptr;
			return (fmt);
		}
		else
			break ;
		ptr++;
	}
	*format = ptr;
	return (fmt);
}

void	set_flags(t_format *fmt, char flag)
{
	if (flag == '-')
		fmt->left_align = 1;
	if (flag == '+')
		fmt->show_sign = 1;
	if (flag == ' ')
		fmt->space = 1;
	if (flag == '#')
		fmt->alt_form = 1;
	if (flag == '0')
		fmt->zero_pad = 1;
}

void	parse_width_precision(t_format *fmt, const char **ptr)
{
	if (**ptr == '.')
	{
		(*ptr)++;
		fmt->precision = 0;
		while (ft_isdigit(**ptr))
		{
			fmt->precision = fmt->precision * 10 + (**ptr - '0');
			(*ptr)++;
		}
		(*ptr)--;
	}
	else
	{
		while (ft_isdigit(**ptr))
		{
			fmt->width = fmt->width * 10 + (**ptr - '0');
			(*ptr)++;
		}
		(*ptr)--;
	}
}

size_t	handle_format(char *str, size_t size, const char **format, va_list args)
{
	t_format	fmt;
	size_t		len;
	size_t		pos;

	pos = 0;
	fmt = parse_format(format);
	if (fmt.type == 'd' || fmt.type == 'i')
		len = handle_int(str, size, va_arg(args, int), pos, fmt);
	else if (fmt.type == 'u')
		len = handle_uint(str, size, va_arg(args, unsigned int), pos, fmt);
	else if (fmt.type == 'x' || fmt.type == 'X')
		len = handle_hex(str, size, va_arg(args, unsigned int), pos, fmt);
	else if (fmt.type == 'p')
		len = handle_ptr(str, size, va_arg(args, void *), pos, fmt);
	else if (fmt.type == 's')
		len = handle_string(str, size, va_arg(args, char *), pos, fmt);
	else if (fmt.type == 'c')
		len = handle_char(str, size, va_arg(args, int), pos);
	else if (fmt.type == 'f')
		len = handle_float(str, size, va_arg(args, double), pos, fmt);
	else if (fmt.type == '%')
		len = handle_percent(str, size, pos);
	else
		len = 0;
	(*format)++;
	return (len);
}

size_t	handle_padding(char *str, size_t size, const char *src, size_t pos, t_format fmt)
{
	size_t	len;
	size_t	pad;
	char	pad_char;

	len = ft_strlen(src);
	if ((size_t)fmt.width > len)
	{
		pad = fmt.width - len;
		if (fmt.zero_pad && !fmt.left_align)
			pad_char = '0';
		else
			pad_char = ' ';
		if (!fmt.left_align)
			pos += write_padding(str, size, pos, pad_char, pad);
		pos += write_str(str, size, pos, src);
		if (fmt.left_align)
			pos += write_padding(str, size, pos, ' ', pad);
		return (fmt.width);
	}
	return (write_str(str, size, pos, src));
}

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

size_t	handle_int(char *str, size_t size, int value, size_t pos, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_itoa(value);
	if (!num_str)
		return (0);
	len = handle_padding(str, size, num_str, pos, fmt);
	free(num_str);
	return (len);
}

size_t	handle_uint(char *str, size_t size, unsigned int value, size_t pos, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_utoa(value);
	if (!num_str)
		return (0);
	len = handle_padding(str, size, num_str, pos, fmt);
	free(num_str);
	return (len);
}

size_t	handle_hex(char *str, size_t size, unsigned int value, size_t pos, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_utoa_base(value, 16);
	if (!num_str)
		return (0);
	if (fmt.type == 'X')
		ft_strtoupper(num_str);
	len = handle_padding(str, size, num_str, pos, fmt);
	free(num_str);
	return (len);
}

size_t	handle_ptr(char *str, size_t size, void *value, size_t pos, t_format fmt)
{
	char	*addr_str;
	size_t	len;

	addr_str = ft_ptoa(value);
	if (!addr_str)
		return (0);
	len = handle_padding(str, size, addr_str, pos, fmt);
	free(addr_str);
	return (len);
}

size_t	handle_string(char *str, size_t size, char *value, size_t pos, t_format fmt)
{
	size_t	len;

	if (!value)
		value = "(null)";
	len = handle_padding(str, size, value, pos, fmt);
	return (len);
}

size_t	handle_char(char *str, size_t size, int value, size_t pos)
{
	char	c;

	c = (char)value;
	if (str && pos < size - 1)
		str[pos] = c;
	pos++;
	return (pos);
}

size_t	handle_float(char *str, size_t size, double value, size_t pos, t_format fmt)
{
	char	*num_str;
	size_t	len;

	num_str = ft_ftoa(value, fmt.precision);
	if (!num_str)
		return (0);
	len = handle_padding(str, size, num_str, pos, fmt);
	free(num_str);
	return (len);
}

size_t	handle_percent(char *str, size_t size, size_t pos)
{
	if (str && pos < size - 1)
		str[pos] = '%';
	pos++;
	return (pos);
}
