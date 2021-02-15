/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:04:05 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/15 14:54:58 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "timestamp.h"

int		g_philo_count;
int		g_time_to_die;
int		g_time_to_eat;
int		g_time_to_sleep;
int		g_time_must_eat;
int		g_end;
t_philo	*g_philos;

void	*philo_thread(void *arg)
{
	int			ff;
	int			sf;
	t_philo		*philo;

	philo = arg;
	ff = (philo->no % 2 ? philo->no : philo->no + 1) % g_philo_count;
	sf = (philo->no % 2 ? philo->no + 1 : philo->no) % g_philo_count;
	while (!g_end)
	{
		pickup_fork(ff, philo->no);
		pickup_fork(sf, philo->no);
		philo->state = STATE_EAT;
		print_log(philo->no, LOG_EAT);
		ft_sleep(g_time_to_eat);
		philo->last_eat = get_timestamp();
		philo->time_eat++;
		return_fork(ff);
		return_fork(sf);
		philo->state = STATE_SLEEP;
		print_log(philo->no, LOG_SLEEP);
		ft_sleep(g_time_to_sleep);
		philo->state = STATE_THINK;
	}
	return (NULL);
}

void	init_global(void)
{
	int				i;
	unsigned long	t;

	i = 0;
	g_end = 0;
	g_philos = malloc(sizeof(t_philo) * g_philo_count);
	i = 0;
	t = get_timestamp();
	while (i < g_philo_count)
	{
		g_philos[i].last_eat = t;
		g_philos[i].time_eat = 0;
		g_philos[i].state = STATE_THINK;
		g_philos[i].no = i;
		i++;
	}
}

void	philo(void)
{
	int			i;
	pthread_t	*tids;
	pthread_t	monitor_tid;

	init_timestamp();
	init_global();
	tids = malloc(sizeof(pthread_t) * g_philo_count);
	init_fork(g_philo_count);
	i = -1;
	while (++i < g_philo_count)
	{
		pthread_create(&tids[i], NULL, philo_thread, &g_philos[i]);
		pthread_detach(tids[i]);
	}
	pthread_create(&monitor_tid, NULL, monitor_thread, NULL);
	pthread_join(monitor_tid, NULL);
	destroy_fork(g_philo_count);
	free(g_philos);
	free(tids);
}

int		main(int argc, char **argv)
{
	if (argc != 6 && argc != 5)
	{
		printf("Bad Arguments!\n");
		return (1);
	}
	g_philo_count = ft_atoi(argv[1]);
	g_time_to_die = ft_atoi(argv[2]);
	g_time_to_eat = ft_atoi(argv[3]);
	g_time_to_sleep = ft_atoi(argv[4]);
	g_time_must_eat = argc == 6 ? ft_atoi(argv[5]) : -1;
	philo();
	return (0);
}
