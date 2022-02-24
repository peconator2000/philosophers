/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:09:16 by vellie            #+#    #+#             */
/*   Updated: 2022/01/19 19:41:11 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->phnum)
	{
		((info->ph)[i]).eat_num = 0;
		((info->ph)[i]).num = i;
		((info->ph)[i]).info = info;
		((info->ph)[i]).eating = 0;
		((info->ph)[i]).last_eat = info->timestart;
		if (i != info->phnum - 1)
		{
			((info->ph)[i]).lfork = i;
			((info->ph)[i]).rfork = i + 1;
		}
		else
		{
			((info->ph)[i]).lfork = 0;
			((info->ph)[i]).rfork = i;
		}
		i++;
	}
}

static int	forks_init(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(t_mutex) * info->phnum);
	info->stop = malloc(sizeof(t_mutex) * info->phnum);
	if (!(info->forks) || !(info->stop))
		return (1);
	while (i < info->phnum)
	{
		pthread_mutex_init(&((info->forks)[i]), NULL);
		pthread_mutex_init(&((info->stop)[i]), NULL);
		i++;
	}
	return (0);
}

static int	args_checker(t_info *info, char **argv)
{
	info->dead = 0;
	info->phnum = ft_atoi(argv[1]);
	info->time_to_death = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->is_static)
	{
		info->how_eat = ft_atoi(argv[5]);
		if (info->how_eat <= 0)
			return (1);
	}
	if (info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (1);
	if (info->phnum <= 0 || info->phnum >= 200 || info->time_to_death <= 0)
		return (1);
	return (0);
}

int	info_enter(int argc, char **argv, t_info *info)
{
	if (argc != 5 && argc != 6)
		return (1);
	info->is_static = 0;
	info->full_num = 0;
	info->how_eat = -1;
	if (argc == 6)
		info->is_static = 1;
	if (args_checker(info, argv))
		return (1);
	return (0);
}

int	info_init(t_info *info)
{
	info->ph = malloc(sizeof(t_philo) * info->phnum);
	if (!(info->ph))
		return (1);
	philo_init(info);
	if (forks_init(info))
		return (1);
	info->ph_tr = malloc(sizeof(t_thread) * info->phnum);
	if (!(info->ph_tr))
		return (1);
	pthread_mutex_init((info->stop), NULL);
	info->timestart = gettime();
	time_manager(info->ph);
	return (0);
}
