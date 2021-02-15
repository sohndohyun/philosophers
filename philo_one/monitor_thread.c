/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:42:55 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/15 01:17:50 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include "timestamp.h"

int		is_philo_death(void)
{
	int i;

	i = 0;
	while (i < g_philo_count)
	{
		if (g_philos[i].state != STATE_EAT &&
			(int)(get_timestamp() - g_philos[i].last_eat) >= g_time_to_die)
			return (i);
		i++;
	}
	return (-1);
}

int		is_must_eat(void)
{
	int i;

	if (g_time_must_eat == -1)
		return (0);
	i = 0;
	while (i < g_philo_count)
	{
		if (g_philos[i].time_eat < g_time_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_thread(void *arg)
{
	int n;

	n = (int)arg;
	while (1)
	{
		if ((n = is_philo_death()) != -1)
		{
			print_log(n, LOG_DIE);
			break ;
		}
		if (is_must_eat())
			break ;
		usleep(5000);
	}
	g_end = 1;
	usleep(1000);
	return (NULL);
}
