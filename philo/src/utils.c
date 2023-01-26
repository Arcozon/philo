/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 08:19:55 by geudes            #+#    #+#             */
/*   Updated: 2023/01/14 10:58:37 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

unsigned int	gt(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0))
		return (0);
	return (1000 * time.tv_sec + time.tv_usec / 1000);
}

void	freep(int test, void *p1, void *p2, void *p3)
{
	if (test)
	{
		free(p1);
		free(p2);
		free(p3);
	}
}

void	error(int test, char *error_msg, void *p1, void *p2)
{
	if (!test)
		return ;
	write(2, error_msg, ft_strlen(error_msg));
	free(p1);
	free(p2);
	exit(test);
}

unsigned int	ft_atoui(char *str)
{
	unsigned int	nb;
	unsigned int	i;

	i = 0;
	nb = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i != ft_strlen(str))
		(printf("Bro stop please.\n"), exit(0));
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}
