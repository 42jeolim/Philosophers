/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:54:57 by jeolim            #+#    #+#             */
/*   Updated: 2023/03/12 17:45:14 by jeolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

// void checking(void)
// {
// 	system("leaks philo");
// }

int	main(int argc, char **argv)
{
	t_data	data;

	if (check(argc, argv))
		return (1);
	if (var_init(&data, argc, argv))
		return (error_print("Input Error\n"));
	if (philo_work(&data, (&data)->philo))
		return (error_print("Working Error\n"));
	// atexit(checking);
	return (0);
}
