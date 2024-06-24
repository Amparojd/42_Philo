/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:14 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/24 20:06:35 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	finish_simulation(t_philo *philo)
{
	long	time;

	time = get_current_time() - philo->philoenv->start_time;
	pthread_mutex_lock(&philo->philoenv->check_stop);
	philo->philoenv->stop_time = 0;
	pthread_mutex_unlock(&philo->philoenv->check_stop);
	ph_usleep(1);
	pthread_mutex_lock(&philo->philoenv->msg);
	printf(COMMON, time, philo->id);
	printf(DIE_MESSAGE);
	pthread_mutex_unlock(&philo->philoenv->msg);
}

int	check_finished(t_philoenv *data)
{
	int	breaker;

	pthread_mutex_lock(&data->check_stop);
	pthread_mutex_lock(&data->check_fin_eating);
	breaker = data->stop_time;
	if (breaker && data->num_fin_eating == data->num_philos)
		breaker = 0;
	pthread_mutex_unlock(&data->check_fin_eating);
	pthread_mutex_unlock(&data->check_stop);
	if (breaker)
		return (0);
	return (1);
}

void	check_fin_eating(t_philoenv *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
	if (data->num_meals != -1 && philo->meals_eaten == data->num_meals)
	{
		pthread_mutex_lock(&data->check_fin_eating);
		data->num_fin_eating++;
		pthread_mutex_unlock(&data->check_fin_eating);
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
			pthread_mutex_lock(&philo->deadline_mutex);
			time = philo->deadline;
			pthread_mutex_unlock(&philo->deadline_mutex);
			if (get_current_time() > time)
				return (finish_simulation(philo), NULL);
		}
		ph_usleep(1);
	}
	return (NULL);
}
