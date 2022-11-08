/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:01:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/08 19:50:38 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

//Program runs the philosopher exercise.
int	main(int argc, char **argv)
{
	t_set	table;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (isvalidnum(argv[i]) == 0 || isinteger(argv[i]) == 0)
			return (-1);
		i++;
	}
	if (argc == 5 || argc == 6)
	{
		table.numphi = ft_atoi(argv[1]);
		table.timedie = ft_atoi(argv[2]);
		table.timeeat = ft_atoi(argv[3]);
		table.timeslp = ft_atoi(argv[4]);
		table.reqeat = 0;
		if (argc == 6)
			table.reqeat = ft_atoi(argv[5]);
		printf("Philosophers: %6d\n", table.numphi);
		printf("Starve time : %6d\n", table.timedie);
		printf("Time to eat : %6d\n", table.timeeat);
		printf("Sleep time  : %6d\n", table.timeslp);
		printf("Times to eat: %6d\n", table.reqeat);
	}
	return (0);
}