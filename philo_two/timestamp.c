/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 23:17:07 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/15 01:19:00 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

unsigned long g_begin;

void			init_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	g_begin = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

unsigned long	get_timestamp(void)
{
	struct timeval	tv;
	unsigned long	temp;

	gettimeofday(&tv, NULL);
	temp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (temp - g_begin);
}
