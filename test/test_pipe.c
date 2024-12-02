/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2002/12/20 12:35:32 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 12:50:27 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		pipefd[2];
	char	buffer[256];
	int		pid;

	// Création du pipe
	if (pipe(pipefd) == -1)
	{
		perror("Erreur lors de la création du pipe");
		return (1);
	}
	// Création d'un processus enfant
	pid = fork();

	if (pid == -1) 
	{
		perror("Erreur lors de la création du processus enfant");
		return (1);
	}
	if (pid == 0)
	{
		// Code du processus enfant
		close(pipefd[0]); // Ferme l'extrémité de lecture du pipe

		// Écriture dans le pipe
		char message[] = "Bonjour du processus enfant!";
		write(pipefd[1], message, sizeof(message));
		close(pipefd[1]); // Ferme l'extrémité d'écriture du pipe
	}
	else
	{
		// Code du processus parent
		close(pipefd[1]); // Ferme l'extrémité d'écriture du pipe

		// Lecture depuis le pipe
		int nbytes = read(pipefd[0], buffer, sizeof(buffer));
		printf("Message reçu du processus enfant : %.*s\n", nbytes, buffer);
		close(pipefd[0]); // Ferme l'extrémité de lecture du pipe
	}
	return (0);
}
