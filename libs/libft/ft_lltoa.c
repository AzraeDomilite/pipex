/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2028/11/20 14:14:59 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 14:15:45 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa(long long n, long long nb)
{
	char		*str;
	int			len;
	int			sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		nb = -n;
	}
	else
		nb = n;
	len = ft_numlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > sign)
	{
		str[len] = '0' + (nb % 10);
		nb /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
