/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:57:39 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/09 13:04:56 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//Typedef describes a fork on the philosopher table.
typedef struct s_fork
{
	int	available;
}		t_fork;

//Typedef describes a philosopher as a node in a circular doubly-linked list.
typedef struct s_philo
{
	int				num;
	int				eatct;
	struct s_philo	*prev_ph;
	struct s_philo	*next_ph;
	t_fork			*prev_f;
	t_fork			*next_f;
}					t_philo;

//Typedef describes the philosopher table.
typedef struct s_table
{
	int		members;
	int		forks;
	t_philo	*first_ph;
	t_philo	*last_ph;
	t_fork	*first_f;
	t_fork	*last_f;
}			t_table;

//Typedef stores conditions/settings for the philosopher exercise.
typedef struct s_set
{
	int	numphi;
	int	timedie;
	int	timeeat;
	int	timeslp;
	int	reqeat;
}		t_set;

// MEMORY HANDLING
//Function frees the memory used up in the table.
void	freetable(t_table *table);

// INPUT HANDLING
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

// SETTING CREATION
//Function creates and initialises a fork.
t_fork	*initfork(t_fork *fork);
//Function creates and initialises a philosopher.
t_philo	*initphilo(t_philo *philo);
//Function creates and initialises a table.
t_table	*inittable(t_table *table);
//Function adds a philosopher (and his corresponding fork) to the table.
void	addphilo(t_table *table);
#endif
