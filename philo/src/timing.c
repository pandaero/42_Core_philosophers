/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:42:50 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/11 23:36:28 by pandalaf         ###   ########.fr       */
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

//Function works out the timestamp of a philosopher's last meal.
void	workouttsmeal(t_data *data, t_philo *philo)
{
	workoutts(data);
	philo->mealtime = data->tmst->absms - philo->mealtime;
}

//Function works out the starvation timestamp.
void	workouttsstarve(t_data *data, t_philo *philo)
{
	philo->philotod = data->tmst->absms;
}

//Function prints out an event.
void	printevent(t_data *data, t_philo *philo, char ch)
{
	workoutts(data);
	if (ch == 'f')
		printf("%08ld %2d has taken a fork\n", data->tmst->absms, philo->num);
	if (ch == 'e')
	{
		printf("%08ld %2d is eating\n", data->tmst->absms, philo->num);
		workouttsmeal(data, philo);
	}
	if (ch == 's')
		printf("%08ld %2d is sleeping\n", data->tmst->absms, philo->num);
	if	(ch == 't')
		printf("%08ld %2d is thinking\n", data->tmst->absms, philo->num);
	if (ch == 'd')
	{
		workouttsstarve(data, philo);
		printf("%08ld %2d died\n", philo->philotod, philo->num);
	}
}
