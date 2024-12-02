/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:19:05 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:42:08 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_join_and_free(char *int_str, char *frac_str)
{
	char	*result;

	result = ft_strjoin(int_str, frac_str);
	free(int_str);
	free(frac_str);
	return (result);
}
