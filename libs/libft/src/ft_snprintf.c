/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:43:10 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:43:11 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_snprintf.h"
#include "../include/libft.h"

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
