/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:42:50 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/12 01:46:18 by pandalaf         ###   ########.fr       */
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
	philo->mealtime = data->tmst->absms - philo->mealtime;
	if (philo->eatct == data->rules->reqeat)
	{
		data->eaten += 1;
		if (data->eaten == data->table->members)
			printf("%08ld  All the philosohers are fed!\n", data->tmst->absms);
	}
}

//Function prints out an event.
void	printevent(t_data *data, t_philo *philo, char ch)
{
	workoutts(data);
	if (ch == 'p')
	{
		philo->prev_f->available = 0;
		printf("%08ld %2d has taken a fork\n", data->tmst->absms, philo->num);
	}
	if (ch == 'f')
	{
		philo->next_f->available = 0;
		printf("%08ld %2d has taken a fork\n", data->tmst->absms, philo->num);
	}
	if (ch == 'e')
		printf("%08ld %2d is eating\n", data->tmst->absms, philo->num);
	if (ch == 's')
		printf("%08ld %2d is sleeping\n", data->tmst->absms, philo->num);
	if	(ch == 't')
		printf("%08ld %2d is thinking\n", data->tmst->absms, philo->num);
	if (ch == 'd')
		printf("%08ld %2d died\n", data->tmst->absms, philo->num);
}
