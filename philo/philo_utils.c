/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:10:42 by vellie            #+#    #+#             */
/*   Updated: 2022/01/19 22:10:03 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_info *info)
{
	if (info->ph)
		free(info->ph);
	if (info->ph_tr)
		free(info->ph_tr);
	if (info->forks)
		free(info->forks);
	if (info->stop)
		free(info->stop);
	return (0);
}

long int	gettime(void)
{
	t_timev	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	msg(char *str, t_philo *ph, int death, int eat)
{
	long int	time;

	time = gettime() - ph->info->timestart;
	if (!(ph->info->dead) || death)
	{
		if (eat)
			printf("[%ld]ms		%d %s	[%d]times\n", \
			time, ph->num, str, ph->eat_num);
		else
			printf("[%ld]ms		%d %s\n", time, ph->num, str);
	}
}

void	time_manager(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->info->phnum)
	{
		ph[i].last_eat = ph->info->timestart;
		i++;
	}
}
