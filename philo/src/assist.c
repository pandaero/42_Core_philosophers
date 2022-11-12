/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:39:47 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/12 20:09:16 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

//Function represents a thread that checks for philosophers starving.
void	*medical_examiner(void *arg)
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
			philo->state->starved = 1;
			data->starved += 1;
			if (data->starved == 1)
				printevent(data, philo, 'd');
		}
		philo = philo->next_ph;
		i++;
	}
	return (0);
}

//Function represents a philosopher thread.
void	*philosopher(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *) arg;
	philo = findphilonum(data);
	if (beginning(data, philo) == 0)
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

//Function performs actions at the beginning of each philosopher thread.
int	beginning(t_data *data, t_philo *philo)
{
	usleep(100);
	if ((philo->eatct >= data->rules->reqeat && data->rules->reqeat > 0) || \
			philo->eatct > findmineat(data))
		return (0);
	if (philo->num % 2 == 0)
		usleep(250);
	if (philo->prev_f->available == 0 || philo->next_f->available == 0)
		return (0);
	return (1);
}

//Function starts and joins the observer and philosopher threads.
int	threading(t_data *data, pthread_t *threads, int i)
{
	while (data->starved == 0 && data->eaten != data->table->members)
	{
		if (pthread_create(&threads[0], 0, medical_examiner, data) != 0)
			return (-1);
		i = 1;
		while (i <= data->rules->numphi)
		{
			data->philonum = i;
			if (pthread_create(&threads[i], 0, philosopher, data) != 0)
				return (-1);
			i++;
		}
		while (i < data->rules->numphi)
		{
			if (pthread_join(threads[i], 0) != 0)
				return (-1);
			i++;
		}
		if (pthread_join(threads[0], 0) != 0)
			return (-1);
	}
	return (0);
}
