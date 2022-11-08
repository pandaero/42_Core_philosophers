/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:57:39 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/08 19:42:26 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

//Typedef describes a philosopher as a node in a circular doubly-linked list.
typedef struct s_philo
{
	int		num;
	int		eatct;
	int		rfork;
	int		lfork;
	void	*next;
	void	*prev;
}		t_philo;

//Typedef stores conditions for the philosopher exercise.
typedef struct s_set
{
	int	numphi;
	int	timedie;
	int	timeeat;
	int	timeslp;
	int	reqeat;
}		t_set;

//Function checks whether a character is a numeric digit.
int		ft_isdigit(int ch);
//Function checks whether a string contains an integer-valid number.
int		isinteger(char *str);
//Function checks whether a string contains a valid signed numeric declaration.
int		isvalidnum(char *str);
//Function returns an integer with the value contained in the given char string.
int		ft_atoi(char *str);
//Function returns a long int with the value contained in the given char string.
long	ft_atol(char *str);

#endif
