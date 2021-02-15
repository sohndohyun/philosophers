/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:14:10 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/15 03:14:09 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t	*g_sem;
sem_t	*g_lock;

void	init_fork(int fork_count)
{
	sem_unlink("forks");
	g_sem = sem_open("forks", O_CREAT, S_IRWXU, fork_count);
	sem_unlink("lock");
	g_lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
}

void	pickup_fork(int philo)
{
	int i;

	i = 0;
	sem_wait(g_lock);
	sem_wait(g_sem);
	print_log(philo, LOG_FORK);
	sem_wait(g_sem);
	print_log(philo, LOG_FORK);
	sem_post(g_lock);
}

void	return_fork(void)
{
	sem_post(g_sem);
	sem_post(g_sem);
}

void	destroy_fork(void)
{
	sem_close(g_sem);
	sem_close(g_lock);
}
