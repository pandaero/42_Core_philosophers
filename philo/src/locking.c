/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:04:24 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 22:31:05 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

static void	lockingforks_odd(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->next_f->mfork);
	printevent(data, philo, 'f');
	if (philo->prev_f)
	{
		pthread_mutex_lock(&philo->prev_f->mfork);
		printevent(data, philo, 'p');
		printevent(data, philo, 'e');
		feeding(data, philo);
	}
	else
	{
		while (data->starved == 0)
			usleep(100);
	}
}

//Function handles locking forks.
void	lockingforks(t_data *data, t_philo *philo)
{
	if (philo->num % 2 == 1)
		lockingforks_odd(data, philo);
	else
	{
		pthread_mutex_lock(&philo->prev_f->mfork);
		printevent(data, philo, 'p');
		if (philo->next_f)
		{
			pthread_mutex_lock(&philo->next_f->mfork);
			printevent(data, philo, 'f');
			printevent(data, philo, 'e');
			feeding(data, philo);
		}
	}
}

//Function handles unlocking forks.
void	unlockingforks(t_data *data, t_philo *philo)
{
	if (philo->num % 2 == 1)
	{
		pthread_mutex_unlock(&philo->next_f->mfork);
		pthread_mutex_unlock(&philo->prev_f->mfork);
	}
	else
	{
		pthread_mutex_unlock(&philo->prev_f->mfork);
		pthread_mutex_unlock(&philo->next_f->mfork);
	}
	printevent(data, philo, 's');
}
