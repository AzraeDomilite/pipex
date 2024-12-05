/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:45:07 by blucken           #+#    #+#             */
/*   Updated: 2024/12/03 11:45:24 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char* get_path()
{
	extern char **environ;
	char* env_path = NULL;
	for (int i = 0; environ[i] != NULL; i++) {
		if (strncmp(environ[i], "PATH=", 5) == 0) {
			env_path = environ[i] + 5;
			break;
		}
	}
	if (env_path == NULL) {
		return NULL;
	}
	char* path = strdup(env_path);
	return path;
}

int main()
{
	char* path = get_path();
	if (path != NULL) {
		printf("PATH: %s\n", path);
		free(path);
	}
	return 0;
}
