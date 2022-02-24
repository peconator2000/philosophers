/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:28:24 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 18:29:33 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_checker(void *inform)
{
	int			id;
	long int	time;
	long int	deathtime;
	t_info		*info;

	info = (t_info *)inform;
	id = info->curnum;
	deathtime = info->time_to_death;
	while (!(info->dead))
	{
		time = gettime();
		if ((time > info->ph[id].last_eat + deathtime
				&& !(((info->ph)[id]).eating)) || info->phnum == 1)
		{
			info->dead = 1;
			info->end = 1;
			msg("IS DEAD", &(info->ph[id]), 1, 0);
			exit(0);
		}
		if ((info->ph[id].eat_num == info->how_eat + 1) && info->is_static)
			info->dead = 1;
	}
	return (NULL);
}
