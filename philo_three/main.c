/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:04:05 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/16 02:07:29 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "timestamp.h"

int		g_philo_count;
int		g_time_to_die;
int		g_time_to_eat;
int		g_time_to_sleep;
int		g_time_must_eat;
t_philo	*g_philos;

void	*philo_thread_monitor(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (!check_die(philo))
	{
		check_eat_max(philo);
		usleep(50);
	}
	return (NULL);
}

void	philo_thread(t_philo *philo)
{
	pthread_t tid;

	pthread_create(&tid, NULL, philo_thread_monitor, philo);
	pthread_detach(tid);
	while (1)
	{
		check_die(philo);
		pickup_fork(philo->no);
		philo->state = STATE_EAT;
		print_log(philo->no, LOG_EAT);
		ft_sleep(g_time_to_eat);
		philo->last_eat = get_timestamp();
		philo->time_eat++;
		return_fork();
		philo->state = STATE_SLEEP;
		print_log(philo->no, LOG_SLEEP);
		ft_sleep(g_time_to_sleep);
		philo->state = STATE_THINK;
	}
}

void	init_global(void)
{
	int				i;
	unsigned long	t;

	i = 0;
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
	init_monitor();
}

void	philo(void)
{
	int			i;
	pid_t		*pids;

	init_timestamp();
	init_global();
	pids = malloc(sizeof(pid_t) * g_philo_count);
	init_fork(g_philo_count);
	i = -1;
	while (++i < g_philo_count)
		if ((pids[i] = fork()) == 0)
		{
			philo_thread(&g_philos[i]);
			exit(0);
		}
	monitor_thread(pids);
	destroy_fork();
	free(g_philos);
	free(pids);
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
