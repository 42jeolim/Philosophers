/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:23 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/12 15:43:09 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (data->n_philo < 2)
		pthread_detach(philo[0].thread);
	else 
	{
		while (i < data->n_philo)
			pthread_join(philo[i++].thread, NULL);
	}
	i = 0;
	while (i < philo->data->n_philo)
		pthread_mutex_destroy(&(philo->data->fork[i++]));
	free(philo->data->philo);
	free(philo->data->fork);
	pthread_mutex_destroy(&(philo->data->mutex_eating));
	pthread_mutex_destroy(&(philo->data->message));
}

int	philo_init(t_data *data)
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
		data->philo[i].last_eat = 0;
		i++;
	}
	return (0);
}

int	fork_init(t_data *data)
{
	int				i;

	i = 0;
	if (data->n_philo < 0 || data->n_philo > 200 || data->time_to_die < 0 || \
		data->time_to_eat < 0 || data->time_to_sleep < 0 || data->must_eat < 0)
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
	if (pthread_mutex_init(&data->message, NULL))
		return (-1);
	if (pthread_mutex_init(&data->mutex_eating, NULL))
		return (-1);
	if (fork_init(data))
		return (-1);
	if (philo_init(data))
		return (-1);
	return (0);
}
