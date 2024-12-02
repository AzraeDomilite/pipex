/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:20:53 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:41:51 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	process_fractional_part(char *frac_str, double frac_part, int precision)
{
	int	i;

	frac_str[0] = '.';
	i = 1;
	while (i <= precision)
	{
		frac_part *= 10;
		frac_str[i] = ((int)frac_part % 10) + '0';
		frac_part -= (int)frac_part;
		i++;
	}
	frac_str[i] = '\0';
}

int	handle_allocation(char **int_str, char **frac_str,
	long long int_part, int precision)
{
	*int_str = ft_lltoa(int_part, 0);
	if (!(*int_str))
		return (0);
	*frac_str = (char *)malloc(precision + 2);
	if (!(*frac_str))
	{
		free(*int_str);
		return (0);
	}
	return (1);
}

char	*ft_ftoa(double n, int precision)
{
	long long	int_part;
	double		frac_part;
	char		*int_str;
	char		*frac_str;

	int_part = (long long)n;
	frac_part = n - (double)int_part;
	if (frac_part < 0)
		frac_part = -frac_part;
	if (!handle_allocation(&int_str, &frac_str, int_part, precision))
		return (NULL);
	process_fractional_part(frac_str, frac_part, precision);
	return (ft_join_and_free(int_str, frac_str));
}
