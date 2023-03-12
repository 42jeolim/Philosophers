/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:23 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/05 16:41:53 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (error_print("Invalid Parameter\n"));
	i = 1;
	while (i < argc)
	{
		if (check_num(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (error_print("Parameter Error\n"));
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

int philo_init(t_data *data)
{
	int		i;

	i = 0;
	data->philo = malloc(sizeof(t_data) * data->n_philo);
	if (!(data->philo))
		return (-1);
	while (i < data->n_philo)
	{
		data->philo[i].id = i;
		data->philo[i].data = data;
		data->philo[i].count = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->n_philo;
		i++;
	}
	return (0);
}

int fork_init(t_data *data)
{
	int				i;

	i = 0;
	if (data->n_philo < 2 || data->time_to_die < 0 \
			|| data->time_to_eat < 0 || data->time_to_sleep < 0 \
			|| data->must_eat < 0 || data->n_philo > 200)
		return (-1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!(data->fork))
		return (-1);
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	var_init(t_data *data, int argc, char **argv)
{
	if (pthread_mutex_init(&data->message, NULL))
		return (-1);
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->finish = 0;
	data->must_eat = 0;
	data->is_eating = 0;
	data->t_start = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (fork_init(data))
		return (-1);
	if (philo_init(data))
		return (-1);
	return (0);
}
