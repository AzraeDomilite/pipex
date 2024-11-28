/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:23:09 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 20:23:23 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SNPRINTF_H
# define FT_SNPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

size_t	handle_input(char *str, size_t size, const char *format, va_list args);
size_t	handle_format(char *str, size_t size, const char **format, va_list args);
t_format	parse_format(const char **format);
void	set_flags(t_format *fmt, char flag);
void	parse_width_precision(t_format *fmt, const char **ptr);
size_t	handle_padding(char *str, size_t size, const char *src, size_t pos, t_format fmt);
size_t	write_str(char *str, size_t size, size_t pos, const char *src);
size_t	write_padding(char *str, size_t size, size_t pos, char pad_char, size_t count);
size_t	handle_int(char *str, size_t size, int value, size_t pos, t_format fmt);
size_t	handle_uint(char *str, size_t size, unsigned int value, size_t pos, t_format fmt);
size_t	handle_hex(char *str, size_t size, unsigned int value, size_t pos, t_format fmt);
size_t	handle_ptr(char *str, size_t size, void *value, size_t pos, t_format fmt);
size_t	handle_string(char *str, size_t size, char *value, size_t pos, t_format fmt);
size_t	handle_char(char *str, size_t size, int value, size_t pos);
size_t	handle_float(char *str, size_t size, double value, size_t pos, t_format fmt);
size_t	handle_percent(char *str, size_t size, size_t pos);

#endif
