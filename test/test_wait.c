/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:51:11 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 12:51:22 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		// Child process
		printf("Child process\n");
		sleep(2);
		exit(0);
	}
	else
	{
		// Parent process
		printf("Parent process\n");
		wait(&status); // Wait for the child process to finish
		if (WIFEXITED(status))
			printf("Child process exited with status: %d\n", WEXITSTATUS(status));
	}

	return (0);
}
