// Tests for functions in timing.c
#include "test.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*Test for workoutts. cc -Wall -Werror -Wextra timing_main.c ../timing.c
int	main(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->tmst = (t_timestamp *)malloc(sizeof(t_timestamp));
	gettimeofday(&data->tmst->rt, 0);
	sleep(2);
	usleep(150000);
	gettimeofday(&data->tmst->t, 0);
	workoutts(data);
	printf("Timestamp: %08ld\n", data->tmst->absms);
	free(data->tmst);
	free(data);
	return (0);
}
//*/

/*Test for printevent. cc -Wall -Werror -Wextra timing_main.c ../timing.c
int	main(void)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)malloc(sizeof(t_data));
	data->tmst = (t_timestamp *)malloc(sizeof(t_timestamp));
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->num = 1;
	gettimeofday(&data->tmst->rt, 0);
	usleep(5000);
	printevent(data, philo, 'f');
	usleep(15000);
	printevent(data, philo, 'e');
	usleep(35000);
	printevent(data, philo, 's');
	usleep(45000);
	printevent(data, philo, 'd');	
	free(philo);
	free(data->tmst);
	free(data);
}
//*/
