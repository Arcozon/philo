/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 13:06:34 by geudes            #+#    #+#             */
/*   Updated: 2023/01/05 04:13:56 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_thread(t_threads thread)
{
	int	i;

	free(thread.philos);
	free(thread.forks);
	i = -1;
	while (++i < thread.nb_philo)
		pthread_mutex_destroy(thread.mutex + i);
	free(thread.mutex);
	free(thread.start);
	free(thread.threads);
}

void	launch_threads(t_threads thread)
{
	int	i;

	i = -1;
	while (++i < thread.nb_philo)
		pthread_create(thread.threads + i, 0, me_is_philo, thread.philos + i);
	thread.start[0] = 1;
	i = -1;
	while (++i < thread.nb_philo)
		pthread_join(thread.threads[i], 0);
	free_thread(thread);
}

static t_philo	*init_philos(t_threads threads)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * threads.nb_philo);
	freep(!philos, 0, threads.start, threads.mutex);
	error(!philos, "Where are the philos", threads.forks, threads.threads);
	i = -1;
	while (++i < threads.nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].forks = threads.forks;
		philos[i].mutex = threads.mutex;
		philos[i].nb_philo = threads.nb_philo;
		philos[i].t_d = threads.info.time_die;
		philos[i].start = threads.start;
		philos[i].t_e = threads.info.time_eat;
		philos[i].t_s = threads.info.time_sleep;
		philos[i].need_to_eat = threads.info.need_to_eat;
		philos[i].hmdie = 0;
	}
	return (philos);
}

static int	*init_forks_mutex(int nb, pthread_mutex_t **pmutex)
{
	int	*forks;
	int	i;

	forks = malloc(sizeof(int) * nb);
	error(!forks, "Where are the forks", 0, 0);
	i = -1;
	while (++i < nb)
		forks[i] = 1;
	*pmutex = malloc(sizeof(pthread_mutex_t) * nb);
	error(!(*pmutex), "Where are the mutexs", forks, 0);
	i = -1;
	while (++i < nb)
		pthread_mutex_init((*pmutex) + i, 0);
	return (forks);
}

void	init_thread(t_info info)
{
	t_threads	thread;

	thread.nb_philo = info.nb_philo;
	thread.forks = init_forks_mutex(info.nb_philo, &(thread.mutex));
	thread.info = info;
	thread.threads = malloc(thread.nb_philo * sizeof(pthread_t));
	error(!thread.threads, "Malloc error", thread.forks, thread.mutex);
	thread.start = malloc(1 * sizeof(char));
	freep(!thread.start, 0, 0, thread.mutex);
	error(!thread.start, "Where is the start", thread.forks, thread.threads);
	thread.start[0] = 0;
	thread.philos = init_philos(thread);
	launch_threads(thread);
}
