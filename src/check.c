/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:24:40 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/12 15:42:45 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > 2147483648 && sign == -1)
		return (0);
	if (res > 2147483647 && sign == 1)
		return (-1);
	return ((int)res * sign);
}

int	check(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (error_print("Parameter Error\n"));
	i = 1;
	while (i < argc)
	{
		if (check_num(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (error_print("Invalid Arguments\n"));
		i++;
	}
	return (0);
}


int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
