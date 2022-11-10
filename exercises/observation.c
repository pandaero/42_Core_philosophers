#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//Typedef is for data to be passed to threads
typedef struct s_data
{
	int	adam;
	int	eve;
}		t_data;

//Function represents an observation thread
void	*observer(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	if (data->adam % 5 == 0)
		printf("Adam multiple of 5! - %2d %2d\n", data->adam, data->eve);
	if (data->eve % 10 == 0)
		printf("Eve multiple of 10! - %2d %2d\n", data->adam, data->eve);
	return (0);
}

//Function represents an action thread
void	*thread(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	usleep(100);
	data->adam += 3;
	data->eve += 9;
	return (0);
}

//Program runs a thread supervised by another
int	main(void)
{
	pthread_t	*threads;
	t_data		*data;
	
	threads = (pthread_t *)malloc(2 * sizeof(pthread_t));
	data = (t_data *)malloc(sizeof(t_data));
	data->adam = 0;
	data->eve = 0;
	while (data->eve < 100)
	{
		pthread_create(&threads[0], 0, observer, data);
		pthread_create(&threads[1], 0, thread, data);
		pthread_join(threads[1], 0);
		pthread_join(threads[0], 0);
	}
	free(threads);
	free(data);
}
