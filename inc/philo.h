/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:49:10 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/24 20:06:28 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include "struct.h"
/* Messages to print 

# define COMMON "\033[1;30m%-5ld ms \033[1;31m%d"
# define FORK_MESSAGE "\033[0;36m has taken a fork\033[0m 🍴\n"
# define EAT_MESSAGE "\033[0;33m is eating\033[0m 🍝\n"
# define SLEEP_MESSAGE "\033[0;34m is sleeping\033[0m 💤\n"
# define THINK_MESSAGE "\033[0;32m is thinking\033[0m 💭\n"
# define DIE_MESSAGE "\033[0;31m died 💀\033[0m\n"
*/
/* Simple version */

# define COMMON "%ld %d"
# define FORK_MESSAGE " has taken a fork\n"
# define EAT_MESSAGE " is eating\n"
# define SLEEP_MESSAGE " is sleeping\n"
# define THINK_MESSAGE " is thinking\n"
# define DIE_MESSAGE " died\n" 


/* Functions */

void	ph_usleep(int time);
void	*routine(void *args);
long	get_current_time(void);
void	*check_death(void *args);
int		ft_atoi(const char *str);
int		parser(int argc, char **argv);
int		check_finished(t_philoenv *data);
void	free_env(t_philoenv *data, t_philo *philos);
void	check_fin_eating(t_philoenv *data, t_philo *philo);
void	print_msg(t_philo *philo, enum e_mssg mssg, long time);
t_philoenv	*env_create(char **argv);
t_philo	*philos_create(t_philoenv *data);
void	one_philo(t_philoenv *data);
int	start_simulation(t_philoenv *data, t_philo *philos);
#endif
