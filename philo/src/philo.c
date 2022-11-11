/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:01:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/11 23:58:18 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//Function checks for a philosopher's starvation.
void	starvationcheck(t_data *data, t_philo *philo)
{
	if ((data->tmst->absms - philo->mealtime) >= data->rules->timedie)
		workouttsstarve(data, philo);
}

//Function represents a thread that checks for philosophers starving.
static void	*medical_examiner(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = (t_data *) arg;
	philo = data->table->first_ph;
	i = 1;
	while (i > 0 && i <= data->table->members)
	{
		workoutts(data);
		if (data->tmst->absms - philo->mealtime >= data->rules->timedie)
		{	
			philo->state->starved = 1;
			data->starved = 1;
		}	
		philo = philo->next_ph;
		i++;
	}
	return (0);
}

//Function represents a thread that reports the events at the philosopher table.
static void	*observer(void *arg)
{
	t_data		*data;
	t_philo		*philo;
	int		i;

	data = (t_data *) arg;
	philo = data->table->first_ph;
	i = 1;
	while (i > 0 && i <= data->table->members)
	{
		if (i > data->table->members)
			break ;
		philo->precheck->forks = philo->state->forks;
		philo->precheck->meals = philo->state->meals;
		philo->precheck->dreams = philo->state->dreams;
		philo->precheck->thinks = philo->state->thinks;
		philo->precheck->starved = philo->state->starved;
		philo = philo->next_ph;
		i++;
	}
	usleep(500 + 1000 * (data->rules->timeeat + data->rules->timeslp));
	i = 1;
	while (i > 0 && i <= data->table->members)
	{
		philo->postcheck->forks = philo->state->forks;
		philo->postcheck->meals = philo->state->meals;
		philo->postcheck->dreams = philo->state->dreams;
		philo->postcheck->thinks = philo->state->thinks;
		philo->postcheck->starved = philo->state->starved;
		philo = philo->next_ph;
		i++;
	}
	i = 1;
	while (i > 0 && i <= data->table->members)
	{
		if (philo->postcheck->forks > philo->precheck->forks)
			printevent(data, philo, 'f');
		if (philo->postcheck->forks > philo->precheck->forks + 1)
			printevent(data, philo, 'f');
		if (philo->postcheck->meals > philo->precheck->meals)
			printevent(data, philo, 'e');
		if (philo->postcheck->dreams > philo->precheck->dreams)
			printevent(data, philo, 's');
		if (philo->postcheck->thinks > philo->precheck->thinks)
			printevent(data, philo, 't');
		if (philo->postcheck->starved == 1 || philo->precheck->starved == 1)
			printevent(data, philo, 'd');
		philo = philo->next_ph;
		i++;
	}
	return (0);
}

//Function represents a philosopher thread.
static void	*philosopher(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *) arg;
	philo = findphilonum(data);
	usleep(100);
	if (philo->num % 2 == 0)
		usleep(250);
	//if (philo->prev_f->available == 1 && philo->next_f->available == 1)
	//{
		pthread_mutex_lock(&philo->prev_f->mfork);
		philo->state->forks++;
		pthread_mutex_lock(&philo->next_f->mfork);
		philo->state->forks++;
	//}
	philo->state->meals++;
	usleep(1000 * data->rules->timeeat);
	pthread_mutex_unlock(&philo->prev_f->mfork);
	pthread_mutex_unlock(&philo->next_f->mfork);
	philo->state->dreams++;
	usleep(1000 * data->rules->timeslp);
	philo->state->thinks++;
	return (0);
}

//Function initialises the table and philosopher threads.
int	philosophers(t_set *rules)
{
	pthread_t	*threads;
	t_table		*table;
	t_data		*data;
	int			i;

	threads = 0;
	table = 0;
	data = 0;
	threads = (pthread_t *)malloc((rules->numphi + 2) * sizeof(pthread_t));
	table = inittable(table);
	data = initdata(data, table, rules);
	i = 0;
	while (i < rules->numphi)
	{
		addphilo(table);
		i++;
	}
	gettimeofday(&data->tmst->rt, 0);
	while (data->starved == 0)
	{
		if (pthread_create(&threads[0], 0, medical_examiner, data) != 0)
			return (-1);
		if (pthread_create(&threads[rules->numphi + 1], 0, observer, data) != 0)
			return (-1);
		i = 1;
		while (i <= rules->numphi)
		{
			data->philonum = i;
			if (pthread_create(&threads[i], 0, philosopher, data) != 0)
				return (-1);
			i++;
		}
		while (i < rules->numphi)
		{
			if (pthread_join(threads[i], 0) != 0)
				return (-1);
			i++;
		}
		if (pthread_join(threads[0], 0) != 0)
			return (-1);
		if (pthread_join(threads[rules->numphi + 1], 0) != 0)
			return (-1);
	}
	freedata(data);
	freetable(table);
	return (0);
}

//*Program runs the philosopher exercise.
int	main(int argc, char **argv)
{
	t_set	*rules;
	int		i;

	rules = 0;
	rules = (t_set *)malloc(sizeof(t_set));
	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			if (isvalidnum(argv[i]) == 0 || isinteger(argv[i]) == 0)
				return (-1);
			i++;
		}
		rules->numphi = ft_atoi(argv[1]);
		rules->timedie = ft_atoi(argv[2]);
		rules->timeeat = ft_atoi(argv[3]);
		rules->timeslp = ft_atoi(argv[4]);
		rules->reqeat = 0;
		if (argc == 6)
			rules->reqeat = ft_atoi(argv[5]);
		if (philosophers(rules) == -1)
			return (-1);
		return (0);
	}
	return (-1);
}
//*/
