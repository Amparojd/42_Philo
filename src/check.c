/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:14 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/18 17:48:04 by ampjimen         ###   ########.fr       */
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
	printf(COMMON DIE_MSG, time, philo->pos);
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
	philo->times_eaten++;
	if (data->num_eat != -1 && philo->times_eaten == data->num_eat)
	{
		pthread_mutex_lock(&data->fin_eating_mutex);
		data->num_fin_eating++;
		pthread_mutex_unlock(&data->fin_eating_mutex);
	}
}

void	check_philo_death(t_philoenv *data, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->check_dying_time);
	time = philo->next_dying_tm;
	pthread_mutex_unlock(&philo->check_dying_time);
	if (get_current_time() > time)
	{
		end_simulation(philo);
		pthread_mutex_lock(&data->finish_program_mutex);
		data->finished = 1;
		pthread_mutex_unlock(&data->finish_program_mutex);
	}
}

void	*check_death(void *args)
{
	int			i;
	t_philoenv	*data;

	data = (t_philoenv *)args;
	while (!check_finished(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			check_philo_death(data, &data->philos[i++]);
			if (data->finished)
				return (NULL);
		}
		ph_usleep(1);
	}
	pthread_mutex_lock(&data->finish_program_mutex);
	data->finished = 1;
	pthread_mutex_unlock(&data->finish_program_mutex);
	return (NULL);
}
