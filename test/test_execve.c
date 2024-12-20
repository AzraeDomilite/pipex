/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:38:19 by blucken           #+#    #+#             */
/*   Updated: 2024/12/03 11:38:26 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int	main()
{
	char *args[] = {"ls", "-l", NULL};
	char **env = environ;

	if (execve(args[0], args, env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
