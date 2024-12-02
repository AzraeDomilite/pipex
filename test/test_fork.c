#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Erreur lors de la création du processus fils\n");
		return (1);
	}
	else if (pid == 0)
	{
		// Code exécuté par le processus fils
		printf("Je suis le processus fils (PID: %d)\n", getpid());
	}
	else
	{
		// Code exécuté par le processus parent
		printf("Je suis le processus parent (PID: %d)\n", getpid());
		printf("Le PID de mon fils est: %d\n", pid);
	}

	return (0);
}