/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:19:21 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/16 02:17:36 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct		s_philo
{
	int				time_eat;
	unsigned long	last_eat;
	int				state;
	int				no;
}					t_philo;

# define LOG_FORK 0
# define LOG_EAT 1
# define LOG_SLEEP 2
# define LOG_THINK 3
# define LOG_DIE 4

# define STATE_EAT 0
# define STATE_THINK 1
# define STATE_SLEEP 2

extern int g_philo_count;
extern int g_time_to_die;
extern int g_time_to_eat;
extern int g_time_to_sleep;
extern int g_time_must_eat;
extern int g_end;
extern t_philo *g_philos;

int					ft_atoi(const char *str);
void				ft_sleep(int milis);

void				init_fork(int fork_count);
void				pickup_fork(int philo);
void				return_fork(void);
void				destroy_fork(void);
void				print_log(int n, int type);

void				*monitor_thread();

#endif
