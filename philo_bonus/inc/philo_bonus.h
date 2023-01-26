/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 08:15:14 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 09:55:43 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/ipc.h>
# include <sys/wait.h>
# include <fcntl.h>

# define DIED 0
# define EATING 1
# define FORK 2
# define SLEEP 3
# define THINK 4

# define DODO 20
# define PING 5

# define NAME_SEMA_FORKS "sema_fork"
# define NAME_SEMA_ALIVE "sema_alive"

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
	sem_t			*sema_fork;
	sem_t			*sema_alive;
	int				nb_philo;
	unsigned int	t_start;
	unsigned int	t_d;
	unsigned int	l_e;
	unsigned int	t_e;
	unsigned int	t_s;
	unsigned int	s_s;
	unsigned int	hmdie;
	int				need_to_eat;
}	t_philo;

typedef struct s_forks
{
	int				nb_philo;
	t_philo			philo;
	pid_t			*pid;
	sem_t			*sema_fork;
	sem_t			*sema_alive;
	t_info			info;
}	t_forks;

/*----------------------Forks--------------------------*/
void			init_fork(t_info info);
void			launch_forks(t_forks forks);

/*-----------------This is a philosopher-----------------*/
int				me_is_philo(t_philo p);

/*-----------------------Utils---------------------------*/
void			error(int test, char *error_msg, void *p1, void *p2);
void			freep(int test, void *p1, void *p2, void *p3);
unsigned int	ft_atoui(char *str);
unsigned int	ft_strlen(char *str);
unsigned int	gt(void);

#endif
