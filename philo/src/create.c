/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:47:04 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/10 00:48:02 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

//Function assigns values for when a new philosopher joins.
static void	newphiloassign(t_table *table, t_philo *new_ph, t_fork *new_f)
{
	void	*temp;

	new_ph->num = table->last_ph->num + 1;
	temp = table->last_ph;
	table->last_ph->next_ph = new_ph;
	table->last_ph = new_ph;
	table->last_ph->prev_ph = temp;
	table->last_ph->next_ph = table->first_ph;
	table->first_ph->prev_ph = table->last_ph;
	temp = table->last_f;
	table->last_f = new_f;
	table->first_ph->prev_f = new_f;
	table->last_ph->next_f = new_f;
	table->last_ph->prev_f = temp;
	table->members++;
	table->forks++;
}

//Function adds a philosopher (and his corresponding fork) to the table.
void	addphilo(t_table *table)
{
	t_philo	*new_ph;
	t_fork	*new_f;

	new_ph = 0;
	new_f = 0;
	new_ph = initphilo(new_ph);
	new_f = initfork(new_f);
	if (table->members == 0)
	{
		new_ph->num = 1;
		new_ph->next_f = new_f;
		table->first_ph = new_ph;
		table->last_ph = new_ph;
		table->first_f = new_f;
		table->last_f = new_f;
		table->members++;
		table->forks++;
	}
	else
		newphiloassign(table, new_ph, new_f);
}
