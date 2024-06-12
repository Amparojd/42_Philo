/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:01:09 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/10 19:52:51 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

//enum tasks//
enum e_msg
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEATH
};

/*Structs*/
typedef struct s_philo
{
	int					pos;
	int					times_eaten;
	int					l_fork;
	int					r_fork;
	long				next_dying_tm;
	pthread_mutex_t		check_dying_time;
	pthread_mutex_t		check_times_eaten;
	pthread_t			philo_thread;
	struct philoenv	*environment;
}	t_philo;

/*Simulation environment*/
typedef struct philoenv
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_eat;
	long			start_time;
	int				breaker;
	int				num_fin_eating;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	breaker_check;
	pthread_mutex_t	fin_eating_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		watchThread;
}	t_philoenv;
#endif