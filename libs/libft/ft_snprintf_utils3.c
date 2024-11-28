/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:53:23 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 20:58:26 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"
#include "libft.h"

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

	fmt = parse_format(format);
	if (fmt.type == 'd' || fmt.type == 'i')
		len = handle_int(str, size, va_arg(args, int), fmt);
	else if (fmt.type == 'u')
		len = handle_uint(str, size, va_arg(args, unsigned int), fmt);
	else if (fmt.type == 'x' || fmt.type == 'X')
		len = handle_hex(str, size, va_arg(args, unsigned int), fmt);
	else if (fmt.type == 'p')
		len = handle_ptr(str, size, va_arg(args, void *), fmt);
	else if (fmt.type == 's')
		len = handle_string(str, size, va_arg(args, char *), fmt);
	else if (fmt.type == 'c')
		len = handle_char(str, size, va_arg(args, int), fmt);
	else if (fmt.type == 'f')
		len = handle_float(str, size, va_arg(args, double), fmt);
	else if (fmt.type == '%')
		len = handle_percent(str, size, fmt);
	else
		len = 0;
	(*format)++;
	return (len);
}

size_t handle_padding(char *str, size_t size, const char *src, t_format fmt) {
    size_t len;
    size_t pad;
    size_t pos;
    char pad_char;

    pos = 0;
    len = ft_strlen(src);
    if ((size_t)fmt.width > len) {
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

