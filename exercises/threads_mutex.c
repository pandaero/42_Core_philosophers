#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mails = 0;

void	*routine(void *arg)
{
	pthread_mutex_t	*mut;

	mut = (pthread_mutex_t *) arg;
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(mut);
		mails++;
		pthread_mutex_unlock(mut);
	}
}

int	main(int argc, char* argv)
{
	pthread_t		p1, p2, p3, p4;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, 0);
	if (pthread_create(&p1, 0, &routine, &mutex) != 0)
		return (1);
	if (pthread_create(&p2, 0, &routine, &mutex) != 0)
		return (2);
	if (pthread_create(&p3, 0, &routine, &mutex) != 0)
		return (3);
	if (pthread_create(&p4, 0, &routine, &mutex) != 0)
		return (4);
	if (pthread_join(p1, 0) != 0)
		return (5);
	if (pthread_join(p2, 0) != 0)
		return (6);
	if (pthread_join(p3, 0) != 0)
		return (7);
	if (pthread_join(p4, 0) != 0)
		return (8);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}
