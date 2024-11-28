/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2028/11/20 14:17:34 by blucken           #+#    #+#             */
/*   Updated: 2024/11/28 14:17:56 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
