/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:01:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/15 01:08:36 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>
#include <stdlib.h>

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
	threads = (pthread_t *)malloc((rules->numphi + 1) * sizeof(pthread_t));
	table = inittable(table);
	data = initdata(data, table, rules);
	i = 0;
	while (i < rules->numphi)
	{
		addphilo(table);
		i++;
	}
	gettimeofday(&data->tmst->rt, 0);
	if (threading(data, threads, i) == -1)
		write(2, "Error.\n", 7);
	free(threads);
	freedata(data);
	freetable(table);
	return (0);
}

//Function sets the rules for the philosopher exercise.
static void	settingrules(t_set *rules, int argc, char **argv)
{
	rules->numphi = ft_atoi(argv[1]);
	rules->timedie = ft_atoi(argv[2]);
	rules->timeeat = ft_atoi(argv[3]);
	rules->timeslp = ft_atoi(argv[4]);
	rules->reqeat = 0;
	if (argc == 6)
		rules->reqeat = ft_atoi(argv[5]);
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
			if (isvalidnum(argv[i]) == 0 || isposinteger(argv[i]) == 0)
			{
				write(2, "Error.\n", 7);
				return (-1);
			}
			i++;
		}
		settingrules(rules, argc, argv);
		if (philosophers(rules) == -1)
			return (-1);
		return (0);
	}
	else
		write(2, "Error.\n", 7);
	return (-1);
}
