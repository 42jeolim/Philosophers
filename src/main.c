/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:54:57 by jeolim            #+#    #+#             */
/*   Updated: 2023/02/27 15:04:00 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;

    if (check(argc, argv))
        return (1);
    
    if (var_init(&data, argc, argv) == -1)
        return(error_print("Allocate Failed\n"));
    
    data.finish = 1;
    data.t_start = timestamp();
    philo_work(&data);
    
    // printf("%d %d %d %d\n", data.n_philo, data.time_to_die, data.time_to_eat, data.time_to_sleep);
    // for (int i = 0; i < data.n_philo; i++)
    // {
    //     printf("%d : %d, %d\n", data.philo[i]->id, data.philo[i]->left_fork, data.philo[i]->right_fork);
    // }
    while (data.finish)
        continue ;
    // system("leaks a.out");
    return (0);
}