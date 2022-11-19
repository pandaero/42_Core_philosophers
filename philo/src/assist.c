/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:39:47 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/19 16:32:47 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

void	unlockforks(t_data *data, t_philo *philo)
{
	if (data->table->members == 1)
	{
		pthread_mutex_unlock(&philo->next_f->mfork);
	}
	if (data->table->members > 1)
	{
		pthread_mutex_unlock(&philo->prev_f->mfork);
		pthread_mutex_unlock(&philo->prev_ph->prev_f->mfork);
		pthread_mutex_unlock(&philo->prev_ph->next_f->mfork);
	}
	if (data->table->members > 2)
	{
		pthread_mutex_unlock(&philo->next_ph->prev_f->mfork);
		pthread_mutex_unlock(&philo->next_ph->next_f->mfork);
	}
}

//Function represents a thread that checks for philosophers starving.
void	*medical_examiner(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = (t_data *) arg;
	while (data->starved == 0 && data->eaten < data->table->members)
	{
		philo = data->table->first_ph;
		i = 1;
		while (i <= data->table->members)
		{
			workoutts(data);
			if (data->tmst->absms - philo->mealtime >= data->rules->timedie)
			{
				unlockforks(data, philo);
				data->starved++;
				printevent(data, philo, 'd');
				break ;
			}
			if (data->table->members > 1)
				philo = philo->next_ph;
			i++;
		}
	}
	return (0);
}

//Function performs actions at the beginning of each philosopher thread.
int	beginning(t_data *data, t_philo *philo)
{
	if ((philo->eatct >= data->rules->reqeat && data->rules->reqeat > 0) || \
			philo->eatct > findmineat(data) || \
			data->eaten == data->table->members)
		return (0);
	return (2);
}

//Function represents a philosopher thread.
void	*philosopher(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *) arg;
	philo = findphilonum(data);
	while (data->starved == 0 && data->eaten < data->table->members)
	{
		if (beginning(data, philo) != 2)
		{
			if (beginning(data, philo) == 0)
				continue ;
			if (beginning(data, philo) == 1)
				return (0);
		}
		lockingforks(data, philo);
		mswait(data->rules->timeeat);
		unlockingforks(data, philo);
		mswait(data->rules->timeslp);
		printevent(data, philo, 't');
	}
	return (0);
}

//Function starts and joins the observer and philosopher threads.
int	threading(t_data *data, pthread_t *threads, int i)
{
	if (pthread_create(&threads[0], 0, medical_examiner, data) != 0)
		return (-1);
	i = 1;
	while (i <= data->table->members)
	{
		data->philonum = i;
		if (pthread_create(&threads[i], 0, philosopher, data) != 0)
			return (-1);
		usleep(100);
		i++;
	}
	i = 1;
	while (i <= data->table->members)
	{
		if (pthread_join(threads[i], 0) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(threads[0], 0) != 0)
		return (-1);
	return (0);
}
