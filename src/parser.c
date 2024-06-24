 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:38:01 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/23 19:36:38 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char *c)
{
	int	i;

	i = 0;
	if (*(c + 1) == 0 && *c == '0')
		return (0);
	while (c[i])
	{
		if ((c[i] < '0' || c[i] > '9') && c[i] != '+')
			return (0);
		i++;
	}
	if (i > 9)
		return (0);
	return (1);
}

static int	print_error(int n)
{
	if (n == 1)
	{
		printf("\033[0;31mNumber of arguments must be between 4 and 5:\n");
		printf("\t\033[0;36m1. Number of philosophers\n");
		printf("\t2. Time to die\n");
		printf("\t3. Time to eat\n");
		printf("\t4. Time to sleep\n");
		printf("\t5. (Optional) Number of times philos must eat\033[0m");
	}
	if (n == 2)
		printf("\033[0;31mInvalid value for philosophers.\033[0m");
	if (n == 3)
		printf("\033[0;31mInvalid value for time.\033[0m");
	if (n == 4)
		printf("\033[0;31mInvalid value for times to eat.\033[0m");
	printf("\n\033[0m");
	return (1);
}

static int	flag_empty(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!(argv[i][0]))
			return (1);
	}
	return (0);
}

int	parser(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || flag_empty(argc, argv))
		return (print_error(1));
	if (!ft_isdigit(argv[1]))
		return (print_error(2));
	if (!ft_isdigit(argv[2]) || !ft_isdigit(argv[3]) || !ft_isdigit(argv[4]))
		return (print_error(3));
	if (argv[5] && !ft_isdigit(argv[5]))
		return (print_error(4));
	return (0);
}
