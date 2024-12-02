/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:18:27 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:18:28 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SNPRINTF_H
# define FT_SNPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_write_str
{
	char		*str;
	size_t		size;
	size_t		pos;
	const char	*src;
}				t_write_str;

typedef struct s_padding
{
	size_t		size;
	size_t		pos;
}				t_padding;

size_t		handle_input(char *str, size_t size,
				const char *format, va_list args);
size_t		handle_format(char *str, size_t size,
				const char **format, va_list args);
t_format	parse_format(const char **format);
void		set_flags(t_format *fmt, char flag);
void		parse_width_precision(t_format *fmt, const char **ptr);
size_t		handle_padding(char *str, size_t size,
				const char *src, t_format fmt);
size_t		write_str(char *str, size_t size, size_t pos, const char *src);
size_t		write_padding(char *str, t_padding pad,
				char pad_char, size_t count);
size_t		handle_int(char *str, size_t size, int value,
				t_format fmt);
size_t		handle_uint(char *str, size_t size, unsigned int value,
				t_format fmt);
size_t		handle_hex(char *str, size_t size, unsigned int value,
				t_format fmt);
size_t		handle_ptr(char *str, size_t size, void *value,
				t_format fmt);
size_t		handle_string(char *str, size_t size, char *value,
				t_format fmt);
size_t		handle_char(char *str, size_t size, int value, t_format fmt);
size_t		handle_float(char *str, size_t size, double value,
				t_format fmt);
size_t		handle_percent(char *str, size_t size, t_format fmt);

#endif
