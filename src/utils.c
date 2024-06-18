/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:13:52 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/18 18:01:12 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	philo_msg(t_philo *philo, enum e_msg mssg)
{
	long	time;

	if (check_finished(philo->environment))
		return ;
	pthread_mutex_lock(&philo->environment->msg_mutex);
	time = get_current_time() - philo->environment->start_time;
	if (mssg == FORK)
		printf(COMMON FORK_MSG, time, philo->pos);
	else if (mssg == EAT)
		printf(COMMON EAT_MSG, time, philo->pos);
	else if (mssg == SLEEP)
		printf(COMMON SLEEP_MSG, time, philo->pos);
	else if (mssg == THINK)
		printf(COMMON THINK_MSG, time, philo->pos);
	pthread_mutex_unlock(&philo->environment->msg_mutex);
}

void	ph_usleep(int time)
{
	long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < time)
		usleep(500);
	return ;
}

static void	waint_until_finish(t_philoenv *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->finish_program_mutex);
		if (data->finished)
		{
			pthread_mutex_unlock(&data->finish_program_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->finish_program_mutex);
	}
}

void	free_tasks(t_philoenv *data, t_philo *philos)
{
	int	i;

	i = -1;
	waint_until_finish(data);
	while (++i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&(data->philos[i]).check_dying_time);
	}
	pthread_mutex_destroy(&data->msg_mutex);
	pthread_mutex_destroy(&data->breaker_check);
	pthread_mutex_destroy(&data->fin_eating_mutex);
	pthread_mutex_destroy(&data->finish_program_mutex);
	pthread_mutex_destroy(&data->threads_joined_mutex);
	free(data->forks);
	free(data->shared_fork);
	free(data);
	free(philos);
}
