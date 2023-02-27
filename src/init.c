/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:02:17 by jeolim            #+#    #+#             */
/*   Updated: 2023/02/27 15:32:39 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_work(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philo)
    {
        data->philo[i]->last_eat = timestamp();
        pthread_create(&data->philo[i]->thread, NULL, routine, (void *)data->philo[i]);
        i++;
        usleep(100);
    }
    i = 0;
    while (i < data->n_philo)
    {
        pthread_create(&data->philo[i]->check_death_thread, NULL, check_death, (void *)data->philo[i]);
        i++;
        usleep(100);
    }
}

int philo_init(t_data *data)
{
    int i;

    data->t_start = timestamp();
    i = -1;
    while (++i < data->n_philo)
    {
        data->philo[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
        if (pthread_mutex_init(&data->philo[i].eating, NULL))
            return (-1);
        printf("i : %d\n", i);
        data->philo[i].id = i + 1;
        data->philo[i].last_eat = 0;
        data->philo[i].data = data; 
        data->philo[i].count = 0; 
        data->philo[i].is_eating = 0;
        data->philo[i].left_fork = i;
        data->philo[i].right_fork = (i + 1) % data->n_philo;


        // pthread_mutex_init(&(data->philo[i].left_fork), NULL); // left_fork mutex init
        // if (i == data->n_philo - 1)
        //     data->philo[i].right_fork = &data->philo[0].left_fork;
        // else
        //     data->philo[i].right_fork = &data->philo[i + 1].left_fork;
        // if (pthread_create(&data->philo[i].thread, NULL, &philo_life, &(data->philo[i])) != 0) // 실패 시 그냥 return
        //     return (-1);
    }
    // i = -1;
    // while (++i < data->n_philo)
    //     if(pthread_join(data->philo[i].thread, NULL) != 0)
    //         return (-1);
    return (0);
}

int var_init(t_data *data, int argc, char **argv)
{ 
    int i;
    
    i = 0;
    data->n_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->finish = 1;
    data->philo_eat = 0;
    data->t_start = timestamp();

    printf("%d %d %d %d\n", data->n_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep);
    
    if (argc == 6)
        data->philo_eat = ft_atoi(argv[5]);
    pthread_mutex_init(&data->message, NULL);
    
    if (data->n_philo <= 0 || data->time_to_die <= 0 \
        || data->time_to_eat <= 0 || data->time_to_sleep <= 0 \
        || data->philo_eat <= 0)
        return (1);
    data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
    if (!data->philo || !data->fork)
        return (-1);
    while (i < data->n_philo)
        pthread_mutex_init(&fork[i++], NULL);
    return (0);
}

int check(int argc, char **argv)
{
    int i;

     if (argc != 5 && argc != 6)
        return (error_print("Parameter Error\n"));
    i = 1;
    while (i < argc)
    {
        if (check_num(argv[i]) || ft_atoi(argv[i]) <= 0)
            return(error_print("Invalid Arguments\n"));
        i++;
    }
    return (0);
}   