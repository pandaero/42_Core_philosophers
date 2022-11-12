/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:01:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/12 01:47:20 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
//Function represents a thread that checks for philosophers starving.
static void	*medical_examiner(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = (t_data *) arg;
	philo = data->table->first_ph;
	i = 1;
	while (i > 0 && i <= data->table->members)
	{
		workoutts(data);
		if (data->tmst->absms - philo->mealtime >= data->rules->timedie)
		{	
			printevent(data, philo, 'd');
			philo->state->starved = 1;
			data->starved = 1;
		}
		philo = philo->next_ph;
		i++;
	}
	return (0);
}

//Function represents a philosopher thread.
static void	*philosopher(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *) arg;
	philo = findphilonum(data);
	usleep(100);
	if (philo->eatct >= data->rules->reqeat && data->rules->reqeat > 0)
		return (0);
	if (philo->num % 2 == 0)
		usleep(250);
	if (philo->next_f->available == 0 || philo->prev_f->available == 0)
		return (0);
	pthread_mutex_lock(&philo->prev_f->mfork);
	printevent(data, philo, 'p');
	pthread_mutex_lock(&philo->next_f->mfork);
	printevent(data, philo, 'f');
	printevent(data, philo, 'e');
	usleep(1000 * data->rules->timeeat);
	feeding(data, philo);
	pthread_mutex_unlock(&philo->prev_f->mfork);
	philo->prev_f->available = 1;
	pthread_mutex_unlock(&philo->next_f->mfork);
	philo->next_f->available = 1;
	printevent(data, philo, 's');
	usleep(1000 * data->rules->timeslp);
	printevent(data, philo, 't');
	return (0);
}

//Function initialises the table and philosopher threads.
int	philosophers(t_set *rules)
{
	pthread_t	*threads;
	t_table		*table;
	t_data		*data;
	int			i;

	threads = 0;
	table = 0;
	data = 0;
	threads = (pthread_t *)malloc((rules->numphi + 1) * sizeof(pthread_t));
	table = inittable(table);
	data = initdata(data, table, rules);
	i = 0;
	while (i < rules->numphi)
	{
		addphilo(table);
		i++;
	}
	gettimeofday(&data->tmst->rt, 0);
	while (data->starved == 0 && data->eaten != table->members)
	{
		if (pthread_create(&threads[0], 0, medical_examiner, data) != 0)
			return (-1);
		i = 1;
		while (i <= rules->numphi)
		{
			data->philonum = i;
			if (pthread_create(&threads[i], 0, philosopher, data) != 0)
				return (-1);
			i++;
		}
		while (i < rules->numphi)
		{
			if (pthread_join(threads[i], 0) != 0)
				return (-1);
			i++;
		}
		if (pthread_join(threads[0], 0) != 0)
			return (-1);
	}
	freedata(data);
	freetable(table);
	return (0);
}

//*Program runs the philosopher exercise.
int	main(int argc, char **argv)
{
	t_set	*rules;
	int		i;

	rules = 0;
	rules = (t_set *)malloc(sizeof(t_set));
	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			if (isvalidnum(argv[i]) == 0 || isinteger(argv[i]) == 0)
				return (-1);
			i++;
		}
		rules->numphi = ft_atoi(argv[1]);
		rules->timedie = ft_atoi(argv[2]);
		rules->timeeat = ft_atoi(argv[3]);
		rules->timeslp = ft_atoi(argv[4]);
		rules->reqeat = 0;
		if (argc == 6)
			rules->reqeat = ft_atoi(argv[5]);
		if (philosophers(rules) == -1)
			return (-1);
		return (0);
	}
	return (-1);
}
//*/
