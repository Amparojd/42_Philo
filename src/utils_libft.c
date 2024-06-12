/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:13:38 by ampjimen          #+#    #+#             */
/*   Updated: 2024/06/07 19:35:30 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	if (*(s + 1) == 0 && *s == '0')
		return (0);
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != '+')
			return (0);
		i++;
	}
	if (i > 9)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		neg;
	size_t	num;

	neg = 1;
	num = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num > LONG_MAX && neg == 1)
		return (-1);
	else if (num > LONG_MAX && neg == -1)
		return (0);
	return (neg * num);
}

int	flag_empty(int argc, char **argv)
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
