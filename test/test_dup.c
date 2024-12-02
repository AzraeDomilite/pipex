/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2002/12/20 12:29:45 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 12:49:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	int	new_fd;

	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	new_fd = dup(fd);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}


	if (new_fd == -1)
	{
		perror("dup");
		return (1);
	}

	printf("Le descripteur de fichier original : %d\n", fd);
	printf("Le nouveau descripteur de fichier : %d\n", new_fd);

	close(fd);
	close(new_fd);

	return (0);
}
