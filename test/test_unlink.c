/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unlink.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:50:46 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 12:50:46 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	// Chemin du fichier à supprimer
	char *filename = "/chemin/vers/le/fichier.txt";
	// Supprimer le fichier
	int result = unlink(filename);
	// Vérifier si la suppression a réussi
	if (result == 0)
	{
		printf("Le fichier a été supprimé avec succès.\n");
	}
	else
	{
		perror("Erreur lors de la suppression du fichier");
	}
	return (0);
}
