/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:42:50 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/15 00:34:26 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <sys/time.h>
#include <stdio.h>

//Function works out the timestamp.
void	workoutts(t_data *data)
{
	gettimeofday(&data->tmst->t, 0);
	data->tmst->sec = data->tmst->t.tv_sec - data->tmst->rt.tv_sec;
	data->tmst->msec = data->tmst->t.tv_usec - data->tmst->rt.tv_usec;
	data->tmst->absms = data->tmst->sec * 1000 + (long) data->tmst->msec / 1000;
	if (data->tmst->absms < 0)
		data->tmst->absms = 0;
}

//Function increments feeding counters and prints all-fed condition.
void	feeding(t_data *data, t_philo *philo)
{
	philo->eatct++;
	philo->mealtime = data->tmst->absms;
	if (philo->eatct == data->rules->reqeat)
	{
		data->eaten++;
		if (data->eaten == data->table->members)
			printf("%5ld  All the philosophers are fed!\n", data->tmst->absms);
	}
}

//Function prints out an event.
void	printevent(t_data *data, t_philo *philo, char ch)
{
	if (ch == 'd')
	{
		printf("%5ld %d died\n", data->tmst->absms, philo->num);
		return ;
	}
	if (data->starved == 0)
	{
		workoutts(data);
		if (ch == 'p')
			printf("%5ld %d has taken a fork\n", data->tmst->absms, philo->num);
		if (ch == 'f')
			printf("%5ld %d has taken a fork\n", data->tmst->absms, philo->num);
		if (ch == 'e')
			printf("%5ld %d is eating\n", data->tmst->absms, philo->num);
		if (ch == 's')
			printf("%5ld %d is sleeping\n", data->tmst->absms, philo->num);
		if (ch == 't')
			printf("%5ld %d is thinking\n", data->tmst->absms, philo->num);
	}
}
