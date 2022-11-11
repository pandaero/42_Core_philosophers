// Tests for functions in philo.c (comment-out main)
#include "test.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//Function prototypes
void	starvationcheck(t_data *data, t_philo *philo);

//*Test for starvationcheck. cc -Wall -Werror -Wextra philo_main.c ../philo.c ../timing.c ../utils.c ../search.c ../init.c ../create.c ../end.c
int	main(void)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)malloc(sizeof(t_data));
	philo = (t_philo *)malloc(sizeof(t_philo));
	data->tmst = (t_timestamp *)malloc(sizeof(t_timestamp));
	data->rules = (t_set *)malloc(sizeof(t_set));
	data->rules->timedie = 45;
	philo->mealtime = 0;
	philo->starved = 0;
	gettimeofday(&data->tmst->rt, 0);
	//Philosopher eats at 0
	gettimeofday(&data->tmst->t, 0);
	workouttsmeal(data, philo);
	// Control at 0
	printf("%5ld Philo status: %d, TOLM: %5ld\n", data->tmst->absms, philo->starved, philo->mealtime);
	usleep(25000);
	//Philosopher eats at 25
	gettimeofday(&data->tmst->t, 0);
	workouttsmeal(data, philo);
	//Control at 25
	workoutts(data);
	starvationcheck(data, philo);
	printf("%5ld Philo status: %d, TOLM: %5ld\n", data->tmst->absms, philo->starved, philo->mealtime);
	usleep(15000);
	//Control at 40
	workoutts(data);
	starvationcheck(data, philo);
	printf("%5ld Philo status: %d, TOLM: %5ld\n", data->tmst->absms, philo->starved, philo->mealtime);
	//Time passes
	usleep(27000);
	//Control at 52
	workoutts(data);
	starvationcheck(data, philo);
	printf("%5ld Philo status: %d, TOLM: %5ld\n", data->tmst->absms, philo->starved, philo->mealtime);
	usleep(48000);
	//Control at 100
	workoutts(data);
	starvationcheck(data, philo);
	printf("%5ld Philo status: %d, TOLM: %5ld\n", data->tmst->absms, philo->starved, philo->mealtime);
	free(data->rules);
	free(data->tmst);
	free(philo);
	free(data);
}
//*/