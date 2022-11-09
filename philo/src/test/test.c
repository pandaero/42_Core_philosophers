//Functions for carrting out tests
#include "test.h"
#include <stdio.h>

//Function to display a table and all its data.
void	table_display_full(t_table *table)
{
	t_philo	*node;

	node = table->first_ph;
	if (node == 0)
	{
		printf("Members: %d, Forks: %d\n", table->members, table->forks);
		return ;
	}
	printf("Members: %d, Forks: %d\n", table->members, table->forks);
	printf("First Ph.: %p, Last Ph.: %p\nFirst Fork: %p, Last Fork: %p\n", \
			table->first_ph, table->last_ph, table->first_f, table->last_f);
	printf("------------------------Start (First)------------------------\n");
	printf("Num. | Eat Ct. |        P. Fork | N. Fork | P. Ph. | N. Ph.\n");
	while (node->next_ph != table->first_ph)
	{
		if (table->members == 1)
			break ;
		printf("%3d   %5d %p %p | %p %p\n", node->num, node->eatct, \
				node->prev_f, node->next_f, node->prev_ph, node->next_ph);
		node = node->next_ph;
	}
	printf("%3d   %5d %p %p | %p %p\n", node->num, node->eatct, node->prev_f, \
				node->next_f, node->prev_ph, node->next_ph);
}
