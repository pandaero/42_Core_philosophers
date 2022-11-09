// Tests for the functions in create.c
#include "test.h"

//Test for addphilo. cc -Wall -Werror -Wextra create_main.c ../create.c ../end.c test.c
int	main(void)
{
	t_table	*table;
	int		i;

	table = 0;
	table = inittable(table);
	i = 0;
	while (i < 4)
	{
		addphilo(table);
		i++;
	}
	table_display_full(table);
	freetable(table);
}
