/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_waitpid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:56:58 by blucken           #+#    #+#             */
/*   Updated: 2024/12/02 12:58:10 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void test_waitpid() {
	pid_t pid;
	int status;

	pid = fork();

	if (pid < 0) {
		perror("fork");
		exit(1);
	} else if (pid == 0) {
		// Child process
		printf("Child process with PID %d\n", getpid());
		exit(0);
	} else {
		// Parent process
		printf("Parent process with PID %d\n", getpid());
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			printf("Child process exited with status: %d\n", WEXITSTATUS(status));
		}
	}
}

int main() {
	test_waitpid();
	return 0;
}