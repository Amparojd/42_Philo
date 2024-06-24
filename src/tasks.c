/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:49:51 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/24 20:12:37 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ph_eat(t_philo *philo) {
    t_philoenv *env;
    long time;

    env = philo->philoenv;

    int left_fork = philo->l_fork;
    int right_fork = philo->r_fork;

    // Adquirir tenedores en orden ascendente
    pthread_mutex_lock(&env->forks[left_fork]);
    pthread_mutex_lock(&env->forks[right_fork]);

    time = get_current_time() - env->start_time;
    print_msg(philo, FORK, time);

    pthread_mutex_lock(&philo->deadline_mutex);
    philo->deadline = get_current_time() + philo->philoenv->time_to_die;
    pthread_mutex_unlock(&philo->deadline_mutex);

    time = get_current_time() - env->start_time;
    print_msg(philo, EAT, time);

    check_fin_eating(env, philo);
    ph_usleep(philo->philoenv->time_to_eat);
    pthread_mutex_unlock(&env->forks[right_fork]);
    pthread_mutex_unlock(&env->forks[left_fork]);
}


static void ph_sleep(t_philo *philo) {
    t_philoenv *env = philo->philoenv;
    long time;

    int left_fork = philo->l_fork;
    int right_fork = philo->r_fork;

    if (left_fork < right_fork) {
        pthread_mutex_unlock(&env->forks[left_fork]);
        pthread_mutex_unlock(&env->forks[right_fork]);
    } else {
        pthread_mutex_unlock(&env->forks[right_fork]);
        pthread_mutex_unlock(&env->forks[left_fork]);
    }

    time = get_current_time() - env->start_time;
    print_msg(philo, SLEEP, time);

    ph_usleep(env->time_to_sleep);
}

static void	ph_think(t_philo *philo)
{
	long	time;

	time = get_current_time() - philo->philoenv->start_time;
	print_msg(philo, THINK, time);
}

void	*routine(void *args)
{
	t_philo		*philo;
	t_philoenv	*env;

	philo = (t_philo *)args;
	env = philo->philoenv;
	if (philo->id % 2 == 0)
		ph_usleep(30);
	while (!check_finished(env))
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (0);
}
