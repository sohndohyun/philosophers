/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:42:55 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/16 02:13:01 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "timestamp.h"
#include <pthread.h>
#include <semaphore.h>

sem_t *g_end;
sem_t *g_count;

int		check_die(t_philo *philo)
{
	int i;

	if (philo->state != STATE_EAT &&
		(int)(get_timestamp() - philo->last_eat) >= g_time_to_die)
	{
		print_log(philo->no, LOG_DIE);
		sem_post(g_end);
		i = 0;
		while (i++ < g_philo_count)
			sem_post(g_count);
		return (1);
	}
	return (0);
}

void	check_eat_max(t_philo *philo)
{
	if (g_time_must_eat != -1 && philo->time_eat >= g_time_must_eat)
		sem_post(g_count);
}

void	*monitor_count_thread(void *arg)
{
	int i;

	i = (int)arg;
	i = 0;
	while (i++ < g_philo_count)
		sem_wait(g_count);
	sem_post(g_end);
	return (NULL);
}

void	init_monitor(void)
{
	sem_unlink("check_die");
	g_end = sem_open("check_die", O_CREAT, S_IRWXU, 0);
	sem_unlink("check_count");
	g_count = sem_open("check_count", O_CREAT, S_IRWXU, 0);
}

void	monitor_thread(pid_t *pids)
{
	pthread_t	tid;
	int			i;

	pthread_create(&tid, NULL, monitor_count_thread, NULL);
	pthread_detach(tid);
	sem_wait(g_end);
	i = -1;
	while (++i < g_philo_count)
		kill(pids[i], SIGKILL);
	sem_close(g_end);
	sem_close(g_count);
}
