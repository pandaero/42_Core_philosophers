#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_type
{
	int		i;
	int		j;
	void	*ptr;
}			t_type;

void	*thread(void *arg)
{
	t_type	*mine;

	mine = (t_type *) arg;
	printf("T: arg->i: %d, arg->j: %d, arg->ptr: %p\n", mine->i, mine->j, mine->ptr);
}

int	main(void)
{
	pthread_t	th;
	t_type		*arg;

	arg = (t_type *)malloc(sizeof(t_type));
	arg->i = 0;
	arg->j = 0;
	arg->ptr = 0;
	pthread_create(&th, 0, &thread, (void *) arg);
	pthread_join(th, 0);
	free(arg);
	return (0);
}
