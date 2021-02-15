/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:19:13 by dsohn             #+#    #+#             */
/*   Updated: 2021/02/15 01:19:08 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include "timestamp.h"

int		ft_atoi(const char *str)
{
	unsigned int	res;
	unsigned int	chk;
	int				neg;

	res = 0;
	chk = 214748364;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		++str;
	if (*str == '-')
		neg = -1;
	neg = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		++str;
	while ('0' <= *str && *str <= '9')
	{
		if ((res > chk || (res == chk && *str > '7')) && neg > 0)
			return (-1);
		if ((res > chk || (res == chk && *str > '8')) && neg < 0)
			return (0);
		res = res * 10 + (*str++ - '0');
	}
	return (res * neg);
}

void	ft_sleep(int milis)
{
	unsigned long	start_time;

	start_time = get_timestamp();
	while (get_timestamp() - start_time < (unsigned long)milis)
		usleep(100);
}
