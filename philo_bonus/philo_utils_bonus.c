/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:28:48 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 18:28:50 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_all(t_info *info)
{
	sem_unlink("/forks");
	sem_unlink("/stop");
	if (info->ph)
		free(info->ph);
	if (info->forks)
		sem_close(info->forks);
	if (info->stop)
		sem_close(info->stop);
	if (info->death_tr)
		free(info->death_tr);
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
	sem_wait(ph->info->stop);
	if ((!(ph->info->dead) || death))
	{
		if (eat)
			printf("[%ld]ms		%d %s	[%d]times\n",
				time, ph->num, str, ph->eat_num);
		else
			printf("[%ld]ms		%d %s\n", time, ph->num, str);
	}
	if (death)
		return ;
	sem_post(ph->info->stop);
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
