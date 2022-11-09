/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:01:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/09 20:36:30 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

//Function works out the timestamp.
void	workoutts(t_data *data)
{
	data->tmst->sec = data->tmst->t.tv_sec - data->tmst->rt.tv_sec;
	data->tmst->msec = data->tmst->t.tv_usec - data->tmst->rt.tv_usec;
	data->tmst->absms = data->tmst->sec * 1000 + (long) data->tmst->msec / 1000;
}

//Function represents a philosopher thread.
void	*philosopher(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = (t_data *) arg;
	philo = data->table->first_ph;
	i = 0;
	while (i < data->philonum && data->philonum > 1)
	{
		philo = philo->next_ph;
		i++;
	}
	pthread_mutex_lock(&philo->prev_f->mfork);
	gettimeofday(&data->tmst->t, 0);
	workoutts(data);
	printf("%08ld %2d has taken a fork\n", data->tmst->absms, philo->num);
	pthread_mutex_lock(&philo->next_f->mfork);
	gettimeofday(&data->tmst->t, 0);
	workoutts(data);
	printf("%08ld %2d has taken a fork\n", data->tmst->absms, philo->num);
	gettimeofday(&data->tmst->t, 0);
	workoutts(data);
	printf("%08ld %2d is eating\n", data->tmst->absms, philo->num);
	usleep(1000 * data->rules->timeeat);
	pthread_mutex_unlock(&philo->prev_f->mfork);
	pthread_mutex_unlock(&philo->prev_f->mfork);
	gettimeofday(&data->tmst->t, 0);
	workoutts(data);
	printf("%08ld %2d is sleeping\n", data->tmst->absms, philo->num);
	usleep(1000 * data->rules->timeslp);
	return (0);
}

#include <stdlib.h>
//Function initialises a data type.
t_data	*initdata(t_data *data, t_table *table, t_set *rules)
{
	data->philonum = 0;
	data->rules = rules;
	data->table = table;
	data->tmst = (t_timestamp *)malloc(sizeof(t_timestamp));
	return (data);
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
	threads = (pthread_t *)malloc(rules->numphi * sizeof(pthread_t));
	table = inittable(table);
	data = initdata(data, table, rules);
	i = 0;
	while (i < rules->numphi)
	{
		addphilo(table);
		i++;
	}
	gettimeofday(&data->tmst->rt, 0);
	i = 0;
	while (i < rules->numphi)
	{
		data->philonum = i + 1;
		if (pthread_create(&threads[i], 0, philosopher, data) != 0)
			return(-1);
		i++;
	}
	while (i < rules->numphi)
	{
		pthread_join(threads[i], 0);
		i++;
	}
	freedata(data);
	freetable(table);
	return (0);
}

//Program runs the philosopher exercise.
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
