/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:08:45 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/14 18:39:06 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>
#include <limits.h>

//Function finds a philosopher based on the assigned number.
t_philo	*findphilonum(t_data *data)
{
	t_philo	*philo;

	philo = data->table->first_ph;
	while (philo->num != data->philonum)
		philo = philo->next_ph;
	return (philo);
}

//Function finds the philosopher with the lowest eat count and returns it.
int	findmineat(t_data *data)
{
	t_philo	*philo;
	int		eatmin;
	int		i;

	philo = data->table->first_ph;
	eatmin = philo->eatct;
	i = 1;
	while (data->table->members > 1 && i <= data->table->members)
	{
		if (philo->eatct < eatmin)
			eatmin = philo->eatct;
		philo = philo->next_ph;
		i++;
	}
	return (eatmin);
}
