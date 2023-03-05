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

t_philo	**philo_init(t_data *data)
{
	t_philo	**tmp;
	int		i;

	tmp = (t_philo **)malloc(sizeof(t_philo *) * data->n_philo);
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		tmp[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (!tmp[i])
			return (NULL);
		if (pthread_mutex_init(&tmp[i]->mutex_eating, NULL))
		{
			free(tmp);
			return (NULL);
		}
		tmp[i]->id = i;
		tmp[i]->data = data;
		tmp[i]->is_eating = 0;
		tmp[i]->count = 0;
		tmp[i]->left_fork = i;
		tmp[i]->right_fork = (i + 1) % data->n_philo;
	}
	return (tmp);
}

pthread_mutex_t	*fork_init(t_data *data)
{
	pthread_mutex_t	*tmp;
	int				i;

	i = 0;
	if (data->n_philo < 0 || data->time_to_die < 0 \
			|| data->time_to_eat < 0 || data->time_to_sleep < 0 \
			|| data->must_eat < 0)
		return (NULL);
	tmp = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!tmp)
		return (NULL);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&tmp[i], NULL);
		i++;
	}
	return (tmp);
}

int	var_init(t_data *data, int argc, char **argv)
{
	pthread_mutex_init(&data->message, NULL);
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->finish = 1;
	data->must_eat = 0;
	data->t_start = timestamp();
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->fork = fork_init(data);
	if (!data->fork)
		return (-1);
	data->philo = philo_init(data);
	if (!data->philo)
		return (-1);
	return (0);
}
