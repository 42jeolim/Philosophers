/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:54:50 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/14 13:12:04 by jeolim           ###   ########.fr       */
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

void	pirnt_message(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&(data->message));
	if (!data->finish)
		printf("[%lld]ms\t| %d %s\n", timestamp() - data->t_start, \
				id + 1, str);
	pthread_mutex_unlock(&(data->message));
}

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleeping_time(t_data *data)
{
	long long	sleep_time;
	long long	start_time;
	long long	now_time;

	sleep_time = (long long)(data->time_to_sleep);
	start_time = timestamp();
	while (!(data->finish))
	{
		now_time = timestamp();
		if ((now_time - start_time) >= sleep_time)
			break ;
		usleep(10);
	}
}

void	eating_time(t_data *data)
{
	long long	eat_time;
	long long	start_time;
	long long	now_time;

	eat_time = (long long)(data->time_to_eat);
	start_time = timestamp();
	while (!(data->finish))
	{
		now_time = timestamp();
		if ((now_time - start_time) >= eat_time)
			break ;
		usleep(10);
	}
}
