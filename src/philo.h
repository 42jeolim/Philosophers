/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:25 by jeolim            #+#    #+#             */
/*   Updated: 2023/02/27 15:28:16 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_philo
{
    int             id;
    int             is_eating;
    int             count;
    long int        last_eat;
    int             right_fork;
    int             left_fork;
    pthread_t       thread;
    pthread_t       check_death_thread;
    struct  s_data  *data;
    pthread_mutex_t eating;
}   t_philo;

typedef struct s_data
{
    int             n_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             philo_eat;
    long int        t_start;
    pthread_mutex_t message;
    pthread_mutex_t *fork;
    int             finish;
    t_philo         **philo;
}   t_data;

// init.c
int         var_init(t_data *data, int argc, char **argv);
int         philo_init(t_data *data);
int         check(int argc, char **argv);
void        philo_work(t_data *data);

// philo.c
void        philo_eat(t_philo *philo);
void        take_fork(t_philo *philo);
void        check_eat(t_philo *philo);
void        *check_death(void *philo);
void        *routine(void   *philo);

// utils.c
long long   timestamp(void);
void        ft_usleep(int ms); // check
int         is_dead(t_philo *philo, int n); //check
void        print(t_philo *philo, char *str);
int         error_print(char *str);

// additional
int         check_num(char *str);
int         ft_atoi(const char *str);
void        freeall(t_data *data);

#endif