/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:13:52 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/07 19:28:11 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	philo_msg(t_philo *philo, enum e_msg mssg, long time)
{
	if (check_finished(philo->environment))
		return ;
	pthread_mutex_lock(&philo->environment->msg_mutex);
	printf(COMMON, time, philo->pos);
	if (mssg == FORK)
		printf(FORK_MSG);
	else if (mssg == EAT)
		printf(EAT_MSG);
	else if (mssg == SLEEP)
		printf(SLEEP_MSG);
	else if (mssg == THINK)
		printf(THINK_MSG);
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

void	free_tasks(t_philoenv *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&(data->philos[i]).check_dying_time);
		pthread_mutex_destroy(&(data->philos[i]).check_times_eaten);
	}
	pthread_mutex_destroy(&data->msg_mutex);
	pthread_mutex_destroy(&data->breaker_check);
	pthread_mutex_destroy(&data->fin_eating_mutex);
	free(data->forks);
	free(data);
	free(philos);
}
