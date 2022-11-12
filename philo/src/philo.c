/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:01:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/12 19:46:42 by pandalaf         ###   ########.fr       */
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
			if (data->starved == 1)
				printevent(data, philo, 'd');
			philo->state->starved = 1;
			data->starved += 1;
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
	if (beginning(data) == 0)
		return (0);
	printevent(data, philo, 'p');
	pthread_mutex_lock(&philo->prev_f->mfork);
	printevent(data, philo, 'f');
	pthread_mutex_lock(&philo->next_f->mfork);
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
	if (threading(data) == -1)
		write(2, "Error.\n", 7);
	freedata(data);
	freetable(table);
	return (0);
}

//Function sets the rules for the philosopher exercise.
static void	settingrules(t_set *rules, int argc, char **argv)
{
	rules->numphi = ft_atoi(argv[1]);
	rules->timedie = ft_atoi(argv[2]);
	rules->timeeat = ft_atoi(argv[3]);
	rules->timeslp = ft_atoi(argv[4]);
	rules->reqeat = 0;
	if (argc == 6)
		rules->reqeat = ft_atoi(argv[5]);
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
			if (isvalidnum(argv[i]) == 0 || isposinteger(argv[i]) == 0)
			{
				write(2, "Error.\n", 7);
				return (-1);
			}
			i++;
		}
		settingrules(rules, argc, argv);
		if (philosophers(rules) == -1)
			return (-1);
		return (0);
	}
	else
		write(2, "Error.\n", 7);
	return (-1);
}
//*/
