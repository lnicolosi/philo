/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolosi <lnicolosi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:12:08 by lnicolosi         #+#    #+#             */
/*   Updated: 2025/01/19 16:13:41 by lnicolosi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		pars_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit("Wrong input:\n" G"Correct is ./philo 5 800 200 200 [5]"RST);
	}
}
