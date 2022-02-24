/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:07:59 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 16:19:03 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_checker(t_info *info)
{
	int			i;
	long int	time;
	long int	deathtime;

	i = 0;
	deathtime = info->time_to_death;
	while (!(info->dead) || (!(info->dead) && info->phnum == 1))
	{
		time = gettime();
		pthread_mutex_lock(&(info->stop[i]));
		if (time > info->ph[i].last_eat + deathtime
			&& !(((info->ph)[i]).eating))
		{
			info->dead = 1;
			msg("IS DEAD", &((info->ph)[i]), 1, 0);
		}
		pthread_mutex_unlock(&(info->stop[i]));
		if ((info->full_num == info->phnum) && info->is_static)
			info->dead = 1;
		i = (i + 1) % (info->phnum);
	}
}
