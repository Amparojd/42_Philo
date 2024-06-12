/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:50:04 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/10 20:02:56 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_philoenv *data)
{
	long	time;

	time = get_current_time() - data->start_time;
	philo_msg(&data->philos[0], FORK, time);
	ph_usleep(data->time_to_die);
	printf(COMMON, data->time_to_die, data->philos[0].pos);
	printf(DIE_MSG);
}

static t_philo	*philos_create(t_philoenv *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].pos = i + 1;
		philos[i].times_eaten = 0;
		philos[i].l_fork = i;
		philos[i].r_fork = i + 1;
		if (i + 1 == data->num_philos)
			philos[i].r_fork = 0;
		pthread_mutex_init(data->forks + i, NULL);
		pthread_mutex_init(&(philos[i]).check_dying_time, NULL);
		pthread_mutex_init(&(philos[i]).check_times_eaten, NULL);
		philos[i].next_dying_tm = get_current_time() + data->time_to_die;
		philos[i].environment = data;
		i++;
	}
	data->philos = philos;
	return (philos);
}

static t_philoenv	*start_env(char **argv)
{
	t_philoenv	*data;

	data = malloc(sizeof(t_philoenv));
	if (!data)
		return (NULL);
	data->breaker = 1;
	data->num_fin_eating = 0;
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_eat = -1;
	if (argv[5])
		data->num_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&data->fin_eating_mutex, NULL);
	pthread_mutex_init(&data->msg_mutex, NULL);
	pthread_mutex_init(&data->breaker_check, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (data->forks == NULL)
		return (free(data), NULL);
	return (data);
}

static int	start_simulation(t_philoenv *data, t_philo *philos)
{
	int	i;

	if (data->num_philos == 1)
		return (one_philo(data), 0);
	if (pthread_create(&data->watchThread, NULL, &check_death, (void *)data))
		return (1);
	pthread_detach(data->watchThread);
	i = -1;
	while (++i < data->num_philos)
	{
			if (pthread_create(&((data->philos)[i].philo_thread),
			NULL, &ph_routines, (void *)&philos[i]))
			return (1);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(((data->philos)[i].philo_thread), NULL))
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philoenv	*data;
	t_philo		*philos;

	if (ph_parser(argc, argv))
		return (1);
	data = start_env(argv);
	if (!data)
		return (1);
	philos = philos_create(data);
	if (!philos)
		return (free(data), 1);
	data->start_time = get_current_time();
	if (start_simulation(data, philos))
		return (1);
	free_tasks(data, philos);
	return (0);
}
