// Tests for the functions in search.c
#include "test.h"
#include <stdlib.h>
#include <stdio.h>

/*Test for findmineat. cc -Wall -Werror -Wextra search_main.c ../search.c
int	main(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->table = (t_table *)malloc(sizeof(t_table));
	data->table->first_ph = (t_philo *)malloc(sizeof(t_philo));
	data->table->first_ph->eatct = 3;
	printf("One Philo: mineat: %d\n", findmineat(data));
	free(data->table->first_ph);
	free(data->table);
	free(data);
	return (0);
}
//*/
