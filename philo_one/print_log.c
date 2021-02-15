/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 23:10:39 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/15 01:17:25 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include "timestamp.h"

void	print_log(int n, int type)
{
	if (type == LOG_FORK)
		printf("[%10lums] %3d has taken a fork\n", get_timestamp(), n + 1);
	else if (type == LOG_EAT)
		printf("[%10lums] %3d is eating\n", get_timestamp(), n + 1);
	else if (type == LOG_SLEEP)
		printf("[%10lums] %3d is sleeping\n", get_timestamp(), n + 1);
	else if (type == LOG_THINK)
		printf("[%10lums] %3d is thinking\n", get_timestamp(), n + 1);
	else if (type == LOG_DIE)
		printf("[%10lums] %3d died\n", get_timestamp(), n + 1);
}
