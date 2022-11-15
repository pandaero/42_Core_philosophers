/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:04:24 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/15 02:38:47 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

static void	lockassist(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->next_f->mfork);
	philo->next_f->available = 0;
	printevent(data, philo, 'p');
	printevent(data, philo, 'f');
	printevent(data, philo, 'e');
	feeding(data, philo);
}

#include <stdio.h>
//Function handles locking forks.
void	lockingforks(t_data *data, t_philo *philo)
{
	int	eatct;

	eatct = philo->eatct;
	while (data->starved == 0)
	{
		while (philo->prev_f->available == 0 && philo->next_f->available == 0)
			usleep(500);
		while (philo->prev_f->available == 1 || philo->next_f->available == 1)
		{
			if (data->starved > 0)
				return ;
			pthread_mutex_lock(&philo->prev_f->mfork);
			philo->prev_f->available = 0;
			if (philo->next_f->available == 0)
			{
				usleep(100);
				pthread_mutex_unlock(&philo->prev_f->mfork);
				philo->prev_f->available = 1;
				continue ;
			}
			lockassist(data, philo);
		}
		if (philo->eatct > eatct)
			break ;
	}
}

//Function handles unlocking forks.
int	unlockingforks(t_data *data, t_philo *philo)
{
	if (data->starved > 0)
		return (0);
	pthread_mutex_unlock(&philo->prev_f->mfork);
	philo->prev_f->available = 1;
	pthread_mutex_unlock(&philo->next_f->mfork);
	philo->next_f->available = 1;
	printevent(data, philo, 's');
	return (1);
}
