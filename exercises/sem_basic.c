#include <semaphore.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void	*thread(void *arg)
{
	sem_t	*semaphore;
	int		*data;

	data = (int *) arg;
	printf("Thread started %d\n", *data);
	semaphore = sem_open("Forks", O_CREAT);
	sem_wait(semaphore);
	printf("Halted semaphore\n");
	*data += 1;
	sem_post(semaphore);
	sem_close(semaphore);
	return (0);
}

int	main(void)
{
	pthread_t	*threadid;
	sem_t		*semaphore;
	int			*data;
	int			i;

	data = (int *)malloc(sizeof(int));
	*data = 0;
	semaphore = sem_open("Forks", O_CREAT, S_IRWXU, 2);
	sem_close(semaphore);
	threadid = (pthread_t *)malloc(5 * sizeof(pthread_t));
	i = 0;
	while (i < 5)
	{
		pthread_create(&threadid[i], 0, thread, data);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join(threadid[i], 0);
		i++;
	}
	printf("Threads joined. Data %d\n", *data);
	sem_unlink("Forks");
	free(threadid);
	free(data);
	return (0);
}
