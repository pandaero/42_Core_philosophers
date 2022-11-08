#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int	primes[10] = {1, 2, 3, 5, 7, 13, 17, 19, 23, 29};

//Function executes a thread.
void	*thread(void *arg)
{
	int	index;

	index = *(int *) arg;
	printf("%d ", primes[index]);
	free(arg);
}

//Program executes multiple threads.
int	main(void)
{
	pthread_t	th[10];
	int			*arg;
	int			i;

	i = 0;
	while (i < 10)
	{
		arg = (int *)malloc(sizeof(int));
		*arg = i;
		if (pthread_create(&th[i], 0, &thread, arg) != 0)
			perror("Thread creation error");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], 0) != 0)
			perror("Thread joining error");
		i++;
	}
	return (0);
}
