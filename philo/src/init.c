/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:47:31 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/11 23:54:37 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <pthread.h>

//Function creates and initialises a fork as a mutex.
t_fork	*initfork(t_fork *fork)
{
	fork = (t_fork *)malloc(sizeof(t_fork));
	pthread_mutex_init(&fork->mfork, 0);
	return (fork);
}

//Function initialises a data type.
t_data	*initdata(t_data *data, t_table *table, t_set *rules)
{
	data = (t_data *)malloc(sizeof(t_data));
	data->philonum = 0;
	data->starved = 0;
	data->rules = rules;
	data->table = table;
	data->tmst = (t_timestamp *)malloc(sizeof(t_timestamp));
	return (data);
}

//Function creates and initialises a philosopher.
t_philo	*initphilo(t_philo *philo)
{
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->state = (t_assess *)malloc(sizeof(t_assess));
	philo->precheck = (t_assess *)malloc(sizeof(t_assess));
	philo->postcheck = (t_assess *)malloc(sizeof(t_assess));
	philo->num = 0;
	philo->eatct = 0;
	philo->mealtime = 0;
	philo->philotod = 0;
	philo->prev_ph = 0;
	philo->next_ph = 0;
	philo->prev_f = 0;
	philo->next_f = 0;
	return (philo);
}

//Function creates and initialises a table.
t_table	*inittable(t_table *table)
{
	table = (t_table *)malloc(sizeof(t_table));
	table->members = 0;
	table->forks = 0;
	table->first_ph = 0;
	table->last_ph = 0;
	table->first_f = 0;
	table->last_f = 0;
	return (table);
}
