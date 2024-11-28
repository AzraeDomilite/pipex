/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:06:27 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 19:07:33 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SNPRINTF_H
# define FT_SNPRINTF_H

# include <stdarg.h>
# include <stdlib.h>

typedef struct s_format
{
	char	type;
	int		width;
	int		precision;
	int		zero_pad;
	int		left_align;
	int		show_sign;
	int		space;
	int		alt_form;
}	t_format;

static size_t	handle_format(char *str, size_t size, const char **format,
					va_list args, size_t pos);
static t_format	parse_format(const char **format);
static void		set_flags(t_format *fmt, char flag);
static void		parse_width_precision(t_format *fmt, const char **ptr);
static size_t	handle_padding(char *str, size_t size, const char *src,
					size_t pos, t_format fmt);

#endif

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	int		written;
	size_t	i;
	size_t	count;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += handle_format(str, size, &format[i], args, count);
		else if (str && count < size - 1)
		{
			str[count] = format[i];
			count++;
		}
		i++;
	}
	if (str && size > 0)
	{
		if (count < size)
			str[count] = '\0';
		else
			str[size - 1] = '\0';
	}
	va_end(args);
	return (count);
}

static t_format	parse_format(const char **format)
{
	t_format	fmt;
	const char	*ptr;

	ft_memset(&fmt, 0, sizeof(fmt));
	ptr = *format + 1;
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

static void	set_flags(t_format *fmt, char flag)
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

static void	parse_width_precision(t_format *fmt, const char **ptr)
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

static size_t	handle_format(char *str, size_t size, const char **format,
					va_list args, size_t pos)
{
	t_format	fmt;
	size_t		len;

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
	return (len);
}

static size_t	handle_padding(char *str, size_t size, const char *src,
					size_t pos, t_format fmt)
{
	size_t	len;
	size_t	pad;
	char	pad_char;

	len = ft_strlen(src);
	if (fmt.width > len)
	{
		pad = fmt.width - len;
		pad_char = (fmt.zero_pad && !fmt.left_align) ? '0' : ' ';
		if (!fmt.left_align)
		{
			write_padding(str, size, pos, pad_char, pad);
			pos += pad;
		}
		write_str(str, size, pos, src);
		if (fmt.left_align)
		{
			pos += len;
			write_padding(str, size, pos, ' ', pad);
		}
		return (fmt.width);
	}
	write_str(str, size, pos, src);
	return (len);
}

static void	write_padding(char *str, size_t size, size_t pos,
				char pad_char, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && pos + i < size - 1 && str)
	{
		str[pos + i] = pad_char;
		i++;
	}
}

static void	write_str(char *str, size_t size, size_t pos, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] && pos + i < size - 1 && str)
	{
		str[pos + i] = src[i];
		i++;
	}
}