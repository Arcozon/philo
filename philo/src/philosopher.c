/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:41:54 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 16:16:19 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*g_message[] = {
	"%u %d died\n",
	"%u %d is eating\n",
	"%u %d has taken a fork\n",
	"%u %d is sleeping\n",
	"%u %d is thinking\n"};

static inline int	alive_no_dead(t_philo *p)
{
	return (p->l_e + p->t_d > gt() && p->start[0]);
}

static void	status(t_philo *philo, int msg)
{
	unsigned int	time_ms;

	time_ms = gt() - philo->t_start;
	if (msg > THINK || msg < 0 || !philo->start[0])
		return ;
	philo->start[0] = msg != DIED;
	printf (g_message[msg], time_ms, philo->id);
}

static int	pick_2fork(t_philo *p)
{
	if (p->nb_philo == 1)
		return (0);
	pthread_mutex_lock(p->mutex + p->id -1);
	pthread_mutex_lock(p->mutex + (p->id % p->nb_philo));
	if (p->forks[p->id - 1] && p->forks[(p->id % p->nb_philo)])
	{
		if (!alive_no_dead(p))
			return (pthread_mutex_unlock(p->mutex + p->id -1),
				pthread_mutex_unlock(p->mutex + (p->id % p->nb_philo)), 1);
		p->forks[p->id - 1] = 0;
		p->forks[(p->id % p->nb_philo)] = 0;
		(status(p, FORK), status(p, FORK), status(p, EATING));
		p->l_e = gt();
		while (p->l_e + p->t_e > gt() && alive_no_dead(p))
			usleep(DODO);
		p->forks[p->id - 1] = 1;
		p->forks[(p->id % p->nb_philo)] = 1;
		pthread_mutex_unlock(p->mutex + p->id -1);
		pthread_mutex_unlock(p->mutex + (p->id % p->nb_philo));
		return (1);
	}
	pthread_mutex_unlock(p->mutex + p->id -1);
	pthread_mutex_unlock(p->mutex + (p->id % p->nb_philo));
	return (0);
}

static void	offset_not_the_rapper(t_philo *p)
{
	if (p->nb_philo % 2 && !p->hmdie)
	{
		while (p->id % 3 == 1 && p->l_e + p->t_e > gt() && alive_no_dead(p))
			usleep(DODO);
		while (p->id % 3 == 2 && p->l_e + 2 * p->t_e > gt() && alive_no_dead(p))
			usleep(DODO);
	}
	else if (!p->hmdie)
		while (p->id % 2 && p->l_e + p->t_e > gt() && alive_no_dead(p))
			usleep(DODO);
	if (p->hmdie)
	{
		if (p->nb_philo % 2)
			while (p->l_e + 3 * p->t_e > gt() && alive_no_dead(p))
				usleep(DODO);
		else
			while (p->l_e + 2 * p->t_e > gt() && alive_no_dead(p))
				usleep(DODO);
	}
}

void	*me_is_philo(void *b_philo)
{
	t_philo	*p;

	p = (t_philo *)b_philo;
	wait_for_others(p);
	p->l_e = gt();
	p->t_start = gt();
	while (alive_no_dead(p))
	{
		(status(p, THINK), offset_not_the_rapper(p));
		while (alive_no_dead(p) && !pick_2fork(p))
			usleep(DODO);
		if (!alive_no_dead(p))
			break ;
		p->hmdie++;
		if (p->need_to_eat == (int)p->hmdie)
			break ;
		status(p, SLEEP);
		p->s_s = gt();
		while (p->s_s + p->t_s > gt() && alive_no_dead(p))
			usleep(DODO);
	}
	if (p->l_e + p->t_d <= gt())
		status(p, DIED);
	return (0);
}
