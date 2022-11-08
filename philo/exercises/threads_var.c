#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_args
{
	int	tid;
	int	i;
	int	j;
}		t_args;

//Function serves as a thread.
void	*thread(void *vargp)
{
	int			*arg;
	static int	ct;

	arg = (int *) vargp;
	printf("Thread - start, Value: %d, Count: %d\n", *arg, ct);
	usleep(500);
	ct++;
	printf("Thread - end,   Value: %d, Count: %d\n", *arg, ct);
	return (0);
}

//Program executes multiple threads.
int	main(void)
{
	pthread_t	t1, t2, t3, t4;
	int			i;

	printf("Before threads.\n");
	i = 0;
	pthread_create(&t1, 0, thread, (void *) &t1);
	pthread_create(&t2, 0, thread, (void *) &t2);
	pthread_create(&t3, 0, thread, (void *) &t3);
	pthread_create(&t4, 0, thread, (void *) &t4);
	pthread_join(t1, 0);
	pthread_join(t2, 0);
	pthread_join(t3, 0);
	pthread_join(t4, 0);
	printf("After threads.\n");
	return (0);
}
