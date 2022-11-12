/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:08:45 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/11 23:55:52 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

//Function finds a philosopher based on the assigned number.
t_philo	*findphilonum(t_data *data)
{
	t_philo	*philo;

	philo = data->table->first_ph;
	while (philo->num != data->philonum)
		philo = philo->next_ph;
	return (philo);
}