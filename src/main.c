/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:54:57 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/05 16:43:19 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check(argc, argv))
		return (1);
	if (var_init(&data, argc, argv) == -1)
		return (error_print("Allocate Failed\n"));
	data.finish = 1;
	data.t_start = timestamp();
	philo_work(&data);
	while (data.finish)
		continue ;
	return (0);
}
