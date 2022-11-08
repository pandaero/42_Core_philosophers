/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:14:34 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/08 20:10:51 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <limits.h>

//Function checks whether a character is a numeric digit.
int	ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

//Function checks whether a string contains an integer-valid number.
int	isinteger(char *str)
{
	long	num;

	num = ft_atol(str);
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	return (1);
}

//Function checks whether a string contains a valid signed numeric declaration.
int	isvalidnum(char *str)
{
	int	i;

	if (str[0] == '+' || str[0] == '-')
	{
		i = 1;
		if (str[i] == '\0')
			return (0);
		while (str[i] != '\0')
		{
			if (ft_isdigit(str[i]) == 0)
				return (0);
			i++;
		}
	}
	else
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (ft_isdigit(str[i]) == 0)
				return (0);
			i++;
		}
	}
	return (1);
}

//Function returns an integer with the value contained in the given char string.
int	ft_atoi(char *str)
{
	int		sgn;
	long	sum;

	sum = 0;
	sgn = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sgn *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if (sgn == 1 && sum > INT_MAX)
			return (-1);
		if (sgn == -1 && sum > (long) INT_MAX + 1)
			return (-1);
	}
	return ((int) sgn * sum);
}

//Function returns a long int with the value contained in the given char string.
long	ft_atol(char *str)
{
	int			sgn;
	long long	sum;

	sum = 0;
	sgn = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sgn *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if (sum > LONG_MAX)
			return (-1);
	}
	return ((long) sgn * sum);
}
