/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:04:24 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/15 01:09:14 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

//Function handles locking forks.
void	lockingforks(t_data *data, t_philo *philo)
{
	while (philo->prev_f->available == 0 && philo->next_f->available == 0)
		usleep(100);
	while (philo->prev_f->available == 1 || philo->next_f->available == 1)
	{
		pthread_mutex_lock(&philo->prev_f->mfork);
		philo->prev_f->available = 0;
		if (philo->next_f->available == 0)
		{
			pthread_mutex_unlock(&philo->prev_f->mfork);
			philo->prev_f->available = 1;
			continue ;
		}
		pthread_mutex_lock(&philo->next_f->mfork);
		philo->next_f->available = 0;
		printevent(data, philo, 'p');
		printevent(data, philo, 'f');
		printevent(data, philo, 'e');
		feeding(data, philo);
	}
}

//Function handles unlocking forks.
void	unlockingforks(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&philo->prev_f->mfork);
	philo->prev_f->available = 1;
	pthread_mutex_unlock(&philo->next_f->mfork);
	philo->next_f->available = 1;
	printevent(data, philo, 's');
}
