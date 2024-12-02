/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2028/11/20 13:47:44 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 11:39:09 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libs/libft/libft.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	printf("%d\n", access(av[1], F_OK));
	printf("%d\n", access(av[1], R_OK));
	printf("%d\n", access(av[1], W_OK));
	printf("%d\n", access(av[1], X_OK));
	return (0);
}