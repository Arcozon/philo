/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 08:18:01 by geudes            #+#    #+#             */
/*   Updated: 2023/01/14 10:55:10 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	verif_args(int ac, char **av)
{
	(void)av;
	if (ac < 5)
		return (printf("Gimme more args pwease UwU.\n"), 0);
	if (ac > 6)
		return (printf("Thats to much onee chan :3.\n"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (verif_args(ac, av))
	{
		info.nb_philo = ft_atoui(av[1]);
		if (!info.nb_philo)
			return (printf("Dont do me like that\n"), 0);
		info.time_die = ft_atoui(av[2]);
		info.time_eat = ft_atoui(av[3]);
		info.time_sleep = ft_atoui(av[4]);
		if (ac == 6)
			info.need_to_eat = ft_atoui(av[5]);
		else
			info.need_to_eat = -1;
		if (!info.need_to_eat)
			return (printf("Dont do me like that\n"), 0);
		init_thread(info);
	}
	return (0);
}
