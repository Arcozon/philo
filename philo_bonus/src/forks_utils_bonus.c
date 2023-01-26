/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 13:06:34 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 09:54:00 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_them_all(t_forks forks)
{
	int	i;
	int	return_value;

	i = -1;
	while (++i < forks.nb_philo)
	{
		waitpid(-1, &return_value, 0);
		if (return_value)
		{
			i = -1;
			while (++i < forks.nb_philo)
				if (forks.pid[i] > 0)
					kill(forks.pid[i], SIGKILL);
			return ;
		}
		i++;
	}
}

void	launch_forks(t_forks forks)
{
	int	i;

	i = -1;
	while (++i < forks.nb_philo)
	{
		forks.pid[i] = fork();
		if (!forks.pid[i])
		{
			forks.philo.id = i + 1;
			free(forks.pid);
			i = me_is_philo(forks.philo);
			sem_close(forks.sema_fork);	
			sem_close(forks.sema_alive);
			exit(i);
		}
		else if (forks.pid[i] == -1)
			printf("The philosopher %d didnt come to life.\n", i + 1);
	}
	kill_them_all(forks);
}

static void	init_sema(t_forks *forks)
{
	sem_unlink(NAME_SEMA_FORKS);
	forks->sema_fork = sem_open(NAME_SEMA_FORKS, O_CREAT, 0660,
			forks->nb_philo >> 1);
	if (forks->sema_fork == SEM_FAILED)
		error(1, "Didnt create the semaphore for forks.\n", forks->pid, 0);
	sem_unlink(NAME_SEMA_ALIVE);
	forks->sema_alive = sem_open(NAME_SEMA_ALIVE, O_CREAT, 0660, 1);
	if (forks->sema_alive == SEM_FAILED)
	{
		sem_close(forks->sema_fork);
		error(1, "Didnt create the semaphore for alive.\n", forks->pid, 0);
	}
}

void	init_fork(t_info info)
{
	t_forks	forks;

	forks.nb_philo = info.nb_philo;
	forks.info = info;
	forks.pid = malloc(sizeof(pid_t) * forks.nb_philo);
	if (!forks.pid)
		(printf("Malloc error\n"), exit(0));
	init_sema(&forks);
	forks.philo.nb_philo = forks.nb_philo;
	forks.philo.t_d = forks.info.time_die;
	forks.philo.sema_fork = forks.sema_fork;
	forks.philo.sema_alive = forks.sema_alive;
	forks.philo.t_e = forks.info.time_eat;
	forks.philo.t_s = forks.info.time_sleep;
	forks.philo.need_to_eat = forks.info.need_to_eat;
	forks.philo.hmdie = 0;
	launch_forks(forks);
	sem_close(forks.sema_fork);
	sem_close(forks.sema_alive);
	free(forks.pid);
}
