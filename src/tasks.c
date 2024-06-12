/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:49:51 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/11 21:27:28 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_eat(t_philo *philo)
{
	t_philoenv	*table;
	long		time;

	table = philo->environment;
	pthread_mutex_lock(&table->forks[philo->l_fork]);
	time = get_current_time() - table->start_time;
	philo_msg(philo, FORK, time);
	pthread_mutex_lock(&table->forks[philo->r_fork]);
	time = get_current_time() - table->start_time;
	philo_msg(philo, FORK, time);
	pthread_mutex_lock(&philo->check_dying_time);
	philo->next_dying_tm = get_current_time() + philo->environment->time_to_die;
	pthread_mutex_unlock(&philo->check_dying_time);
	time = get_current_time() - table->start_time;
	philo_msg(philo, EAT, time);
	check_finished_eating(table, philo);
	ph_usleep(philo->environment->time_to_eat);
}

static void	ph_sleep(t_philo *philo)
{
	long	time;

	time = get_current_time() - philo->environment->start_time;
	philo_msg(philo, SLEEP, time);
	pthread_mutex_unlock(&philo->environment->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->environment->forks[philo->r_fork]);
	ph_usleep(philo->environment->time_to_sleep);
}

static void	ph_think(t_philo *philo)
{
	long	time;

	time = get_current_time() - philo->environment->start_time;
	philo_msg(philo, THINK, time);
}

void	*ph_routines(void *args)
{
	t_philo		*philo;
	t_philoenv	*env;

	philo = (t_philo *)args;
	env = philo->environment;
	if (philo->pos % 2 == 0)
		ph_usleep(1);
	while (!check_finished(env))
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (0);
}
