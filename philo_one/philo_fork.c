/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:14:10 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/15 01:18:31 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t *g_mutexes;

void	init_fork(int fork_count)
{
	int i;

	i = 0;
	g_mutexes = malloc(sizeof(pthread_mutex_t) * fork_count);
	while (i < fork_count)
	{
		pthread_mutex_init(&g_mutexes[i], NULL);
		i++;
	}
}

void	pickup_fork(int n, int philo)
{
	pthread_mutex_lock(&g_mutexes[n]);
	print_log(philo, LOG_FORK);
}

void	return_fork(int n)
{
	pthread_mutex_unlock(&g_mutexes[n]);
}

void	destroy_fork(int fork_count)
{
	int i;

	i = 0;
	while (i < fork_count)
	{
		pthread_mutex_destroy(&g_mutexes[i]);
		i++;
	}
	free(g_mutexes);
}
