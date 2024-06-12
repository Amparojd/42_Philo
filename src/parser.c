/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:38:01 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/07 19:36:56 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_philo(int error_num)
{
	if (error_num == 1)
	{
		printf("Number of arguments must be between 4 and 5\n");
		printf("Number of philosophers\n");
		printf("Time to die\n");
		printf("Time to eat\n");
		printf("Time to sleep\n");
		printf("(Option) Number of times philos must eat");
	}
	if (error_num == 2)
		printf("Invalid value for philosophers");
	if (error_num == 3)
		printf("Invalid value for time");
	if (error_num == 4)
		printf("Invalid value for times to eat");
	return (1);
}

int	ph_parser(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || flag_empty(argc, argv))
		return (error_philo(1));
	if (!ft_isdigit(argv[1]))
		return (error_philo(2));
	if (!ft_isdigit(argv[2]) || !ft_isdigit(argv[3]) || !ft_isdigit(argv[4]))
		return (error_philo(3));
	if (argv[5] && !ft_isdigit(argv[5]))
		return (error_philo(4));
	return (0);
}
