/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:41:54 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 09:58:09 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

const char	*g_message[] = {
	"%u %d died\n",
	"%u %d is eating\n",
	"%u %d has taken a fork\n",
	"%u %d is sleeping\n",
	"%u %d is thinking\n"};

static inline int	alive_no_dead(t_philo p)
{
	return (p.l_e + p.t_d > gt());
}

static void	status(t_philo philo, int msg)
{
	unsigned int	time_ms;

	if (msg > THINK || msg < 0)
		return ;
	time_ms = gt() - philo.t_start;
	sem_wait(philo.sema_alive);
	printf (g_message[msg], time_ms, philo.id);
	if (msg != DIED)
		sem_post(philo.sema_alive);
}

static void	pick_2fork(t_philo *p)
{
	sem_wait(p->sema_fork);
	if (!alive_no_dead(*p))
	{
		sem_post(p->sema_fork);
		return ;
	}
	status(*p, FORK);
	status(*p, FORK);
	status(*p, EATING);
	p->l_e = gt();
	while (p->l_e + p->t_e > gt() && alive_no_dead(*p))
		usleep(DODO);
	sem_post(p->sema_fork);
}

static void	offset_not_the_rapper(t_philo p)
{
	if (p.nb_philo % 2 && !p.hmdie)
	{
		while (p.id % 3 == 1 && p.l_e + p.t_e - PING > gt()
			&& alive_no_dead(p))
			usleep(DODO);
		while (p.id % 3 == 2 && p.l_e + p.t_e * 2 - PING > gt()
			&& alive_no_dead(p))
			usleep(DODO);
	}
	else if (!p.hmdie)
		while (p.id % 2 && p.l_e + p.t_e - PING > gt() && alive_no_dead(p))
			usleep(DODO);
	if (p.hmdie)
	{
		if (p.nb_philo % 2)
			while (p.l_e + (3 * p.t_e) - PING > gt() && alive_no_dead(p))
				usleep(DODO);
		else
			while (p.l_e + p.t_e * 2 - PING > gt() && alive_no_dead(p))
				usleep(DODO);
	}
}

int	me_is_philo(t_philo p)
{
	p.l_e = gt();
	p.t_start = gt();
	while (alive_no_dead(p))
	{
		status(p, THINK);
		offset_not_the_rapper(p);
		if (!alive_no_dead(p))
			break ;
		pick_2fork(&p);
		if (!alive_no_dead(p))
			break ;
		p.hmdie++;
		if (p.need_to_eat == (int)p.hmdie)
			break ;
		status(p, SLEEP);
		p.s_s = gt();
		while (p.s_s + p.t_s > gt() && alive_no_dead(p))
			usleep(DODO);
	}
	if (!alive_no_dead(p))
		return (status(p, DIED), 1);
	return (0);
}
