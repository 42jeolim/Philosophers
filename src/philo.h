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
    pthread_t       thread;
    pthread_t       check_death_thread;
    struct  s_data  *data;
    pthread_mutex_t *right_fork;
    pthread_mutex_t left_fork;
    pthread_mutex_t eating;
    struct s_data   *data;
}   t_philo;

typedef struct s_data
{
    int             philo_eat; // all eat
    int             n_philo; // number of philosophers
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             n_eat; // number of eat
    int             finish; // 0: false 1: true
    long int        t_start; // time_to_start
    t_philo         **philo; // shared info
    pthread_mutex_t message;
    pthread_mutex_t m_stop; //?
    pthread_mutex_t m_eat; // ?
    pthread_mutex_t dead; // ?
    pthread_mutex_t *forks;
}   t_data;

// init.c
int         var_init(t_data *data, int argc, char **argv);
int         philo_init(t_data *data);

// philo.c
void        *philo_life(void *philo);

// utils.c
long long   timestamp(void);
void        ft_usleep(int ms); // check
int         is_dead(t_philo *philo, int n); //check
void        print(t_philo *philo, char *str);
int         error_print(char *str);

#endif