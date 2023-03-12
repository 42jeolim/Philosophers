/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:25 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/05 16:22:16 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	int				id;
	int				count;
	long long		last_eat;
	int				right_fork;
	int				left_fork;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		t_start;
	int				finish;
	int				is_eating;
	pthread_mutex_t	message;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_eating;
	t_philo			*philo;
}	t_data;

// philo.c
int			philo_work(t_data *data);

// util.c
int			check(int argc, char **argv);
int			check_num(char *str);
int			var_init(t_data *data, int argc, char **argv);

// additional.c
int			error_print(char *str);
void		pirnt_message(t_philo *philo, char *str);
long long	timestamp(void);
int			ft_atoi(const char *str);
void		sleeping_time(t_philo *philo);
void		eating_time(t_philo *philo);

#endif