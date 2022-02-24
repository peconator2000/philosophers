/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:11:48 by vellie            #+#    #+#             */
/*   Updated: 2022/01/19 22:08:50 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	zero_init(t_info *info)
{
	info->forks = NULL;
	info->ph = NULL;
	info->ph_tr = NULL;
	info->stop = NULL;
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	info;

	i = -1;
	zero_init(&info);
	if (info_enter(argc, argv, &info))
		return (free_all(&info));
	if (info_init(&info))
		return (free_all(&info));
	while (++i < info.phnum)
		pthread_create(&((info.ph_tr)[i]), NULL, philo_move, &((info.ph)[i]));
	death_checker(&info);
	i = -1;
	while (++i < info.phnum)
		pthread_join(info.ph_tr[i], NULL);
	free_all(&info);
	return (0);
}
