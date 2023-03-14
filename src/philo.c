/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:20 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/14 13:15:56 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	pirnt_message(data, "has taken the left fork 🍴", philo->id);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	pirnt_message(data, "has taken the right fork 🍴🍴", philo->id);
	pthread_mutex_lock(&philo->data->mutex_eating);
	pirnt_message(data, "is eating 🍝", philo->id);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->data->mutex_eating);
	philo->count++;
	eating_time(philo->data);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	if (philo->data->is_eating)
		return (-1);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*c_philo;

	c_philo = (t_philo *)philo;
	if (c_philo->id % 2)
		usleep(10000);
	while (!(c_philo->data->finish))
	{
		if (take_fork(c_philo->data, c_philo))
			break ;
		pirnt_message(c_philo->data, "is sleeping 💤", c_philo->id);
		sleeping_time(c_philo->data);
		pirnt_message(c_philo->data, "is thinking 🤔", c_philo->id);
	}
	return (NULL);
}

void	check_eat(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (data->must_eat != 0 && i < data->n_philo \
			&& philo[i].count > data->must_eat)
		i++;
	if (i == data->n_philo)
		data->is_eating = 1;
}

void	check_death(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->is_eating))
	{
		i = 0;
		while ((i < data->n_philo) && (!(data->finish)))
		{
			pthread_mutex_lock(&(data->mutex_eating));
			if ((timestamp() - philo[i].last_eat) >= philo->data->time_to_die)
			{
				pirnt_message(data, "died ☠️", i);
				data->finish = 1;
			}
			pthread_mutex_unlock(&(philo->data->mutex_eating));
			i++;
		}
		if (data->finish)
			break ;
		check_eat(data, philo);
	}
}

int	philo_work(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	data->t_start = timestamp();
	while (i < data->n_philo)
	{
		philo[i].last_eat = timestamp();
		if (pthread_create(&(data->philo[i].thread), NULL, routine, \
					(void *)&(data->philo[i])))
			return (-1);
		i++;
	}
	check_death(data, data->philo);
	end_philo(data, data->philo);
	return (0);
}
