/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:44:25 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 12:47:02 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libs/libft/include/libft.h"

int	main(int ac, char **av, char **env)
{
	if (ac < 2)
	{
		printf("Usage: %s <file>\n", av[0]);
		return (1);
	}

	printf("Checking access for file: %s\n", av[1]);

	if (access(av[1], F_OK) == 0)
		printf("File exists\n");
	else
		printf("File does not exist\n");

	if (access(av[1], R_OK) == 0)
		printf("File is readable\n");
	else
		printf("File is not readable\n");

	if (access(av[1], W_OK) == 0)
		printf("File is writable\n");
	else
		printf("File is not writable\n");

	if (access(av[1], X_OK) == 0)
		printf("File is executable\n");
	else
		printf("File is not executable\n");

	return (0);
}