/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:42:50 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/19 18:20:38 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <sys/time.h>
#include <stdio.h>

//Function works out the timestamp.
void	workoutts(t_data *data)
{
	pthread_mutex_lock(&data->mxtime);
	gettimeofday(&data->tmst->t, 0);
	data->tmst->sec = data->tmst->t.tv_sec - data->tmst->rt.tv_sec;
	data->tmst->msec = data->tmst->t.tv_usec - data->tmst->rt.tv_usec;
	data->tmst->absms = data->tmst->sec * 1000 + (long) data->tmst->msec / 1000;
	if (data->tmst->absms < 0)
		data->tmst->absms = 0;
	pthread_mutex_unlock(&data->mxtime);
}

//Function increments feeding counters and prints all-fed condition.
void	feeding(t_data *data, t_philo *philo)
{
	philo->eatct++;
	philo->mealtime = data->tmst->absms;
	if (philo->eatct == data->rules->reqeat)
	{
		pthread_mutex_lock(&data->mxeaten);
		data->eaten++;
		pthread_mutex_unlock(&data->mxeaten);
		if (data->eaten == data->table->members)
			printf("%5ld All the philosophers are fed!\n", data->tmst->absms);
	}
}

//Function prints out an event.
void	printevent(t_data *data, t_philo *philo, char ch, char *str)
{
	if (ch == 'd')
	{
		printf("%5ld %d %s\n", data->tmst->absms, philo->num, str);
		return ;
	}
	if (data->starved == 0 && data->eaten < data->table->members)
	{
		workoutts(data);
		printf("%5ld %d %s\n", data->tmst->absms, philo->num, str);
	}
}
