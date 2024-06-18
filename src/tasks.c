/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:49:51 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/18 18:13:13 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	release_forks(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(&philo->environment->forks[left]);
	philo->environment->shared_fork[left] = 0;
	pthread_mutex_unlock(&philo->environment->forks[left]);
	pthread_mutex_lock(&philo->environment->forks[right]);
	philo->environment->shared_fork[right] = 0;
	pthread_mutex_unlock(&philo->environment->forks[right]);
	philo->forks = 0;
	check_finished_eating(philo->environment, philo);
}

void	check_fork(t_philo *philo, int pos)
{
	pthread_mutex_lock(&philo->environment->forks[pos]);
	if (philo->environment->shared_fork[pos] == 0)
	{
		philo->environment->shared_fork[pos] = 1;
		philo->forks += 1;
		philo_msg(philo, FORK);
	}
	pthread_mutex_unlock(&philo->environment->forks[pos]);
}

static void	ph_eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->l_fork;
	right = philo->r_fork;
	if (philo->pos % 2 == 0)
	{
		left = philo->r_fork;
		right = philo->l_fork;
	}
	while (philo->forks != 2 && !check_finished(philo->environment))
	{
		check_fork(philo, left);
		check_fork(philo, right);
	}
	pthread_mutex_lock(&philo->check_dying_time);
	philo->next_dying_tm = get_current_time() + philo->environment->time_to_die;
	pthread_mutex_unlock(&philo->check_dying_time);
	philo_msg(philo, EAT);
	ph_usleep(philo->environment->time_to_eat);
	release_forks(philo, left, right);
}

void	*ph_routines(void *args)
{
	t_philo		*philo;
	t_philoenv	*env;
	int			start;

	philo = (t_philo *)args;
	env = philo->environment;
	start = 0;
	while (!start)
	{
		pthread_mutex_lock(&env->threads_joined_mutex);
		start = env->threads_joined;
		pthread_mutex_unlock(&env->threads_joined_mutex);
	}
	if (philo->pos % 2 == 0)
		ph_usleep(1);
	while (!check_finished(env))
	{
		ph_eat(philo);
		philo_msg(philo, SLEEP);
		ph_usleep(philo->environment->time_to_sleep);
		philo_msg(philo, THINK);
	}
	return (0);
}

void	one_philo(t_philoenv *data)
{
	philo_msg(&data->philos[0], FORK);
	ph_usleep(data->time_to_die);
	printf(COMMON, data->time_to_die, data->philos[0].pos);
	printf(DIE_MSG);
	pthread_mutex_lock(&data->finish_program_mutex);
	data->finished = 1;
	pthread_mutex_unlock(&data->finish_program_mutex);
}