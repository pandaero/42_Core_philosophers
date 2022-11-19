/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   further_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:11:02 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/19 16:25:44 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <sys/time.h>

//Function returns a random (up to) 5-digit number based on the current time.
int	randomnum(int max)
{
	int				rand;
	struct timeval	time;

	gettimeofday(&time, 0);
	rand = (int) time.tv_usec % max;
	return (rand);
}

//Function will wait for the input in ms.
void	mswait(long wait)
{
	struct timeval	time;
	struct timeval	starttime;
	long			msstarttime;
	long			msfulltime;

	gettimeofday(&starttime, 0);
	msstarttime = starttime.tv_sec * 1000 + starttime.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&time, 0);
		msfulltime = time.tv_sec * 1000 + time.tv_usec / 1000;
		if (msfulltime >= wait + msstarttime)
			break ;
		usleep(50);
	}
}
