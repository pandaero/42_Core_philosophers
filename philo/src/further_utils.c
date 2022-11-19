/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   further_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:11:02 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 21:02:25 by pandalaf         ###   ########.fr       */
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
