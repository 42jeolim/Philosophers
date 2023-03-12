/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:20 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/05 16:35:10 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	pirnt_message(philo, "has taken the left fork 🍴");
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	pirnt_message(philo, "has taken the right fork 🍴🍴");
	pthread_mutex_lock(&philo->data->mutex_eating);
	// philo->data->is_eating = 1;
	pirnt_message(philo, "is eating 🍝");
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->data->mutex_eating);
	philo->count++;
	// ft_usleep(philo->data->time_to_eat);
	eating_time(philo);
	// philo->data->is_eating = 0;
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
		if (take_fork(c_philo))
			break;
		pirnt_message(c_philo, "is sleeping 💤");
		sleeping_time(philo);
		pirnt_message(c_philo, "is thinking 🤔");
	}
	return (NULL);
}

void	check_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->data->must_eat != 0 && i < philo->data->n_philo \
			&& philo[i].count > philo->data->must_eat)
	i++;
	if (i == philo->data->n_philo)
		philo->data->is_eating = 1;
}

void	check_death(t_philo *philo)
{
	int	i;

	while (!(philo->data->is_eating))
	{
		i = 0;
		while ((i < philo->data->n_philo) && (!(philo->data->finish)))
		{
			pthread_mutex_lock(&philo->data->mutex_eating);
			if ((timestamp() - philo[i].last_eat > philo->data->time_to_die))
			{
				pirnt_message(philo, "died ☠️");
				philo->data->finish = 1;
			}
			pthread_mutex_unlock(&(philo->data->mutex_eating));
			i++;
		}
		if (philo->data->finish)
			break ;
		check_eat(philo);
	}
}

void	end_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < philo->data->n_philo)
		pthread_mutex_destroy(&(philo->data->fork[i++]));
	free(philo->data->philo);
	free(philo->data->fork);
	pthread_mutex_destroy(&(philo->data->mutex_eating));
	pthread_mutex_destroy(&(philo->data->message));
}

int	philo_work(t_data *data)
{
	int		i;

	i = 0;
	data->t_start = timestamp();
	while (i < data->n_philo)
	{
		data->philo[i].last_eat = timestamp();
		if (pthread_create(&data->philo[i].thread, NULL, routine, (void *)(&data->philo[i])))
			return (-1);
		i++;
	}
	check_death(data->philo);
	end_philo(data->philo);
	return (0);
}
