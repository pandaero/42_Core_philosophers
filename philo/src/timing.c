/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:42:50 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/10 00:16:50 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <sys/time.h>
#include <stdio.h>

//Function works out the timestamp.
void	workoutts(t_data *data)
{
	data->tmst->sec = data->tmst->t.tv_sec - data->tmst->rt.tv_sec;
	data->tmst->msec = data->tmst->t.tv_usec - data->tmst->rt.tv_usec;
	data->tmst->absms = data->tmst->sec * 1000 + (long) data->tmst->msec / 1000;
}

//Function prints out an event.
void	printevent(t_data *data, t_philo *philo, char ch)
{
	gettimeofday(&data->tmst->t, 0);
	workoutts(data);
	if (ch == 'f')
		printf("%08ld %2d has taken a fork\n", data->tmst->absms, philo->num);
	if (ch == 'e')
		printf("%08ld %2d is eating\n", data->tmst->absms, philo->num);
	if (ch == 's')
		printf("%08ld %2d is sleeping\n", data->tmst->absms, philo->num);
	if (ch == 'd')
		printf("%08ld %2d died\n", data->tmst->absms, philo->num);
}
