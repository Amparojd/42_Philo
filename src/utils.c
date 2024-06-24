/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:13:52 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/24 19:50:14 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	print_msg(t_philo *philo, enum e_mssg mssg, long time)
{
	if (check_finished(philo->philoenv))
		return ;
	pthread_mutex_lock(&philo->philoenv->msg);
	printf(COMMON, time, philo->id);
	if (mssg == FORK)
		printf(FORK_MESSAGE);
	else if (mssg == EAT)
		printf(EAT_MESSAGE);
	else if (mssg == SLEEP)
		printf(SLEEP_MESSAGE);
	else if (mssg == THINK)
		printf(THINK_MESSAGE);
	pthread_mutex_unlock(&philo->philoenv->msg);
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	num;

	sign = 1;
	num = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num > LONG_MAX && sign == 1)
		return (-1);
	else if (num > LONG_MAX && sign == -1)
		return (0); 
	return (sign * num);
}

void	ph_usleep(int time)
{
	long	start_time;
	long	current_time;
	int		sleep_time;

	start_time = get_current_time();
	while ((current_time = get_current_time()) - start_time < time)
	{
		sleep_time = (time - (current_time - start_time)) / 2;
		if (sleep_time > 0)
			usleep(sleep_time);
	}
}

void	free_env(t_philoenv *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&(data->philos[i]).deadline_mutex);
		pthread_mutex_destroy(&(data->philos[i]).meals_mutex);
	}
	pthread_mutex_destroy(&data->msg);
	pthread_mutex_destroy(&data->check_stop);
	pthread_mutex_destroy(&data->check_fin_eating);
	free(data->forks);
	free(data);
	free(philos);
}
