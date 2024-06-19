/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:49:10 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/18 18:14:11 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

// Define MSG
// #define COMMON "%ld %d"
// #define FORK_MSG "\033[0;33m has taken a fork 🍴\033[0m\n"
// #define EAT_MSG "\033[0;32m is eating 🍜\033[0m\n"
// #define SLEEP_MSG "is sleeping 💤\n"
// #define THINK_MSG "\033[0;35m is thinking 🤔\033[0m\n"
// #define DIE_MSG "\033[0;31m died 💀\033[0m\n"

//Simple version 

#define COMMON "%ld %d"
#define FORK_MSG " has taken a fork\n"
#define EAT_MSG " is eating\n"
#define SLEEP_MSG " is sleeping\n"
#define THINK_MSG " is thinking\n"
#define DIE_MSG " died\n"


//utils libft
int	ft_isdigit(char *s);
int	ft_atoi(const char *str);
int	flag_empty(int argc, char **argv);

//utils
void	free_tasks(t_philoenv *data, t_philo *philos);
void	philo_msg(t_philo *philo, enum e_msg mssg);


//parser
int	ph_parser(int argc, char **argv);
int	error_philo(int error_num);

//tasks
void	ph_usleep(int time);
void	*ph_routines(void *args);
long	get_current_time(void);

//checks finish tasks
void	check_finished_eating(t_philoenv *data, t_philo *philo);
int	check_finished(t_philoenv *data);
void	*check_death(void *args);
void	one_philo(t_philoenv *data);

// main

int	main(int argc, char **argv);

#endif