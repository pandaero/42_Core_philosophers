#include <sys/_types/_timeval.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_timestamp
{
	struct timeval	ref_time;
	struct timeval	time;
}					t_timestamp;

//Program displays a starting time, and timestamps since it.
int	main(void)
{
	t_timestamp	*times;
	
	times = (t_timestamp *)malloc(sizeof(t_timestamp));
	times->ref_time.tv_sec = 0;
	times->ref_time.tv_usec = 0;
	times->time.tv_sec = 0;
	times->time.tv_usec = 0;
	// Get the reference (starting) time
	gettimeofday(&times->ref_time, 0);
	printf("Beginning     : %ld seconds, %d microseconds\n", times->ref_time.tv_sec, times->ref_time.tv_usec);
	usleep(100);
	// Get the second time
	gettimeofday(&times->time, 0);
	printf("One moment    : %ld sec, %d us after beginning.\n", times->time.tv_sec - times->ref_time.tv_sec, times->time.tv_usec - times->ref_time.tv_usec);
	usleep(3000);
	// Get the third time
	gettimeofday(&times->time, 0);
	printf("Another moment: %ld sec, %d ms after beginning.\n", times->time.tv_sec - times->ref_time.tv_sec, (times->time.tv_usec - times->ref_time.tv_usec) / 1000);
	sleep(2);
	// Get a fourth time
	gettimeofday(&times->time, 0);
	printf("Another moment: %ld ms after beginning.\n", (times->time.tv_sec - times->ref_time.tv_sec) * 1000 + (long) (times->time.tv_usec - times->ref_time.tv_usec) / 1000);
	return (0);
}
