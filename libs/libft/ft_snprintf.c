/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:29:03 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 21:02:21 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"
#include "libft.h"

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
