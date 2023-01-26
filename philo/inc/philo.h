/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 08:15:14 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 16:21:36 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define DIED 0
# define EATING 1
# define FORK 2
# define SLEEP 3
# define THINK 4

# define DODO 20

typedef struct s_info
{
	unsigned int	nb_philo;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	int				need_to_eat;
}	t_info;

// t_d: time die
// l_e: last eat
// t_e: time eat
// t_s: time sleep
// s_s: start sleep
// hmdie: how much did i eat
typedef struct s_philo
{
	unsigned int	id;
	int				*forks;
	pthread_mutex_t	*mutex;
	int				nb_philo;
	unsigned int	t_start;
	unsigned int	t_d;
	unsigned int	l_e;
	unsigned int	t_e;
	unsigned int	t_s;
	unsigned int	s_s;
	unsigned int	hmdie;
	int				need_to_eat;
	char			*start;
	pthread_mutex_t	mutex_start;
}	t_philo;

typedef struct s_threads
{
	int				nb_philo;
	t_philo			*philos;
	pthread_t		*threads;
	int				*forks;
	pthread_mutex_t	*mutex;
	t_info			info;
	char			*start;
}	t_threads;

/*----------------------Threads--------------------------*/
void			init_thread(t_info info);
void			launch_threads(t_threads threads);

/*-----------------This is a philosopher-----------------*/
void			*me_is_philo(void *info);

/*-----------------------Utils---------------------------*/
void			error(int test, char *error_msg, void *p1, void *p2);
void			freep(int test, void *p1, void *p2, void *p3);
unsigned int	ft_atoui(char *str);
unsigned int	ft_strlen(char *str);
unsigned int	gt(void);

#endif
