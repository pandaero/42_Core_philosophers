/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:57:39 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/15 09:16:48 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>

//Typedef describes a fork on the philosopher table.
typedef struct s_fork
{
	pthread_mutex_t	mfork;
	int				available;
}					t_fork;

//Typedef describes a philosopher as a node in a circular doubly-linked list.
typedef struct s_philo
{
	int				num;
	int				eatct;
	long			mealtime;
	long			philotod;
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

//Typedef stores data required to print out a timestamp.
typedef struct s_timestamp
{
	struct timeval	rt;
	struct timeval	t;
	long			sec;
	int				msec;
	long			absms;
}					t_timestamp;

//Typedef stores conditions/settings for the philosopher exercise.
typedef struct s_set
{
	int	numphi;
	int	timedie;
	int	timeeat;
	int	timeslp;
	int	reqeat;
}		t_set;

//Typedef stores data required by a philosopher thread to work.
typedef struct s_data
{
	int			philonum;
	int			starved;
	int			eaten;
	int			actions;
	t_set		*rules;
	t_table		*table;
	t_timestamp	*tmst;
}				t_data;

// MEMORY HANDLING
//Function frees the memory used by a fork and its mutex.
void	freefork(t_fork *fork);
//Function frees the memory used up in the table.
void	freetable(t_table *table);
//Function frees memory used by a data type.
void	freedata(t_data *data);

// INPUT HANDLING
//Function checks whether a character is a numeric digit.
int		ft_isdigit(int ch);
//Function checks whether a string contains an integer-valid number.
int		isposinteger(char *str);
//Function checks whether a string contains a valid signed numeric declaration.
int		isvalidnum(char *str);
//Function returns an integer with the value contained in the given char string.
int		ft_atoi(char *str);
//Function returns a long int with the value contained in the given char string.
long	ft_atol(char *str);

// OTHER UTILS
//Function returns a random 5-digit number based on the current time.
int		randomnum(int max);

// MAIN
//Function represents a thread that checks for philosophers starving.
void	*medical_examiner(void *arg);
//Function represents a philosopher thread.
void	*philosopher(void *arg);

// ASSISTING
//Function performs actions at the beginning of each philosopher thread.
int		beginning(t_data *data, t_philo *philo);
//Function starts and joins the observer and philosopher threads.
int		threading(t_data *data, pthread_t *threads, int i);
//Function handles locking forks.
void	lockingforks(t_data *data, t_philo *philo);
//Function handles unlocking forks.
int		unlockingforks(t_data *data, t_philo *philo);

// LOGGING
//Function increments feeding counters and prints all-fed condition.
void	feeding(t_data *data, t_philo *philo);
//Function works out the standard timestamp.
void	workoutts(t_data *data);
//Function prints out an event.
void	printevent(t_data *data, t_philo *philo, char ch);

// SEARCHING
//Function finds a philosopher based on the assigned number.
t_philo	*findphilonum(t_data *data);
//Function finds the philosopher with the lowest eat count and returns it.
int		findmineat(t_data *data);

// INITIALISATION
//Function creates and initialises a fork.
t_fork	*initfork(t_fork *fork);
//Function creates and initialises a philosopher.
t_philo	*initphilo(t_philo *philo);
//Function creates and initialises a table.
t_table	*inittable(t_table *table);
//Function initialises a data type.
t_data	*initdata(t_data *data, t_table *table, t_set *rules);

// SETTING CREATION
//Function adds a philosopher (and his corresponding fork) to the table.
void	addphilo(t_table *table);
#endif
