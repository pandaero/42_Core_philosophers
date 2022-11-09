/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:50:48 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/09 18:48:08 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <pthread.h>

//Function frees the memory used by fork and its mutex.
void	freefork(t_fork *fork)
{
	pthread_mutex_destroy(&fork->mfork);
	free(fork);
}

//Function frees the memory used up in the table.
void	freetable(t_table *table)
{
	t_philo	*cur_ph;
	t_fork	*cur_f;
	void	*temp;

	cur_ph = table->first_ph;
	while (cur_ph != table->last_ph)
	{
		cur_f = cur_ph->next_f;
		freefork(cur_f);
		temp = cur_ph;
		cur_ph = cur_ph->next_ph;
		free(temp);
	}
	cur_f = cur_ph->next_f;
	freefork(cur_f);
	free(cur_ph);
	free(table);
}
