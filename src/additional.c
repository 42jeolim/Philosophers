/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:54:50 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/12 15:26:04 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	return (1);
}

void	pirnt_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->data->message));
	if (!philo->data->finish)
		printf("[%lld]ms\t| %d %s\n", timestamp() - philo->data->t_start, \
				philo->id + 1, str);
	pthread_mutex_unlock(&(philo->data->message));
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	sleeping_time(t_philo *philo)
{
	long long	sleep_time;
	long long	start_time;
	long long	now_time;

	sleep_time = (long long)(philo->data->time_to_die);
	start_time = timestamp();
	while (!(philo->data->finish))
	{
		now_time = timestamp();
		if ((now_time - start_time) >= sleep_time)
			break ;
		usleep(10);
	}
}

void	eating_time(t_philo *philo)
{
	long long	eat_time;
	long long	start_time;
	long long	now_time;

	eat_time = (long long)(philo->data->time_to_eat);
	start_time = timestamp();
	while (!(philo->data->finish))
	{
		now_time = timestamp();
		if ((now_time - start_time) >= eat_time)
			break ;
		usleep(10);
	}
}
