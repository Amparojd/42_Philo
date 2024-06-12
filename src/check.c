/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:14 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/12 13:51:59 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_simulation(t_philo *philo)
{
	long	time;

	time = get_current_time() - philo->environment->start_time;
	pthread_mutex_lock(&philo->environment->breaker_check);
	philo->environment->breaker = 0;
	pthread_mutex_unlock(&philo->environment->breaker_check);
	ph_usleep(1);
	pthread_mutex_lock(&philo->environment->msg_mutex);
	printf(COMMON, time, philo->pos);
	printf(DIE_MSG);
	pthread_mutex_unlock(&philo->environment->msg_mutex);
}

int	check_finished(t_philoenv *data)
{
	int	breaker;

	pthread_mutex_lock(&data->breaker_check);
	pthread_mutex_lock(&data->fin_eating_mutex);
	breaker = data->breaker;
	if (breaker && data->num_fin_eating == data->num_philos)
		breaker = 0;
	pthread_mutex_unlock(&data->fin_eating_mutex);
	pthread_mutex_unlock(&data->breaker_check);
	if (breaker)
		return (0);
	return (1);
}

void	check_finished_eating(t_philoenv *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->check_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->check_times_eaten);
	if (data->num_eat != -1 && philo->times_eaten == data->num_eat)
	{
		pthread_mutex_lock(&data->fin_eating_mutex);
		data->num_fin_eating++;
		pthread_mutex_unlock(&data->fin_eating_mutex);
	}
}

void	*check_death(void *args)
{
	int			i;
	long		time;
	t_philoenv	*data;
	t_philo		*philo;

	data = (t_philoenv *)args;
	while (!check_finished(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			philo = &(data->philos)[i++];
			pthread_mutex_lock(&philo->check_dying_time);
			time = philo->next_dying_tm;
			pthread_mutex_unlock(&philo->check_dying_time);
			if (get_current_time() > time)
				return (end_simulation(philo), NULL);
		}
		ph_usleep(1);
	}
	return (NULL);
}
