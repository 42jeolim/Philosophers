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
    t_data data;

    if (check(argc, argv))
        return (1);
    if (var_init(&data, argc, argv) == 1)
    {
        free(data.philo);
        return(error_print("Init Failed\n"));
    }
    philo_init(&data);
    philo_work(&data);
    while (data.finish)
        continue ;
    freeall(&data);
    return (0); // exit 미제공
}