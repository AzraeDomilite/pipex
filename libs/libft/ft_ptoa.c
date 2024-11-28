/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:20:46 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 20:20:51 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ptoa(void *ptr)
{
	unsigned long	addr;
	char			*str;
	char			*addr_str;
	int				len;

	addr = (unsigned long)ptr;
	addr_str = ft_utoa_base(addr, 16);
	if (!addr_str)
		return (NULL);
	len = ft_strlen(addr_str) + 2;
	str = (char *)malloc(len + 1);
	if (!str)
	{
		free(addr_str);
		return (NULL);
	}
	str[0] = '0';
	str[1] = 'x';
	ft_memcpy(str + 2, addr_str, len - 2);
	str[len] = '\0';
	free(addr_str);
	return (str);
}
