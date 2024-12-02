/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2002/12/20 12:30:52 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 12:49:47 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	buffer[100];

	// Ouvrir un fichier en lecture seule
	fd1 = open("input.txt", O_RDONLY);
	if (fd1 == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (1);
	}
	// Créer un nouveau descripteur de fichier en utilisant dup2()
	fd2 = dup2(fd1, 5);
	if (fd2 == -1)
	{
		perror("Erreur lors de la duplication du descripteur de fichier");
		return (1);
	}
	// Lire à partir du descripteur de fichier dupliqué
	ssize_t bytesRead = read(fd2, buffer, sizeof(buffer));
	if (bytesRead == -1)
	{
		perror("Erreur lors de la lecture du fichier");
		return (1);
	}
	// Afficher le contenu lu
	printf("Contenu du fichier : %.*s\n", (int)bytesRead, buffer);
	// Fermer les descripteurs de fichier
	close(fd1);
	close(fd2);
	return (0);
}
