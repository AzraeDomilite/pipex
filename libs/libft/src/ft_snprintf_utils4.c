/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:41:32 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:41:34 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_snprintf.h"
#include "../include/libft.h"

size_t	handle_input(char *str, size_t size,
			const char *format, va_list args)
{
	size_t		count;
	const char	*ptr;

	count = 0;
	ptr = format;
	while (*ptr)
	{
		if (*ptr == '%' && *(ptr + 1))
			count += handle_format(str, size, &ptr, args);
		else
		{
			if (str && count < size - 1)
				str[count] = *ptr;
			count++;
		}
		ptr++;
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
