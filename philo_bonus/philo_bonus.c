/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:27:40 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 18:29:46 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	zero_init(t_info *info)
{
	info->forks = NULL;
	info->ph = NULL;
	info->death_tr = NULL;
	info->stop = NULL;
}

static void	create_proc(t_info *info, int i)
{
	info->ph[i].pid = fork();
	if (info->ph[i].pid == 0)
	{
		info->curnum = i;
		pthread_create(&(info->death_tr[i]), NULL,
			death_checker, (void *)(info));
		philo_move(&(info->ph[i]));
		pthread_join(info->death_tr[i], NULL);
		if (info->end)
			exit(0);
		else
			exit(1);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	info;
	int		status;

	i = -1;
	zero_init(&info);
	if (info_enter(argc, argv, &info))
		return (0);
	if (info_init(&info))
		return (free_all(&info));
	info.timestart = gettime();
	time_manager(info.ph);
	while (++i < info.phnum)
		create_proc(&info, i);
	i = -1;
	waitpid(-1, &status, 0);
	while (status != 0 && ++i < info.phnum)
		waitpid(-1, &status, 0);
	i = -1;
	while (++i < info.phnum)
		kill(info.ph[i].pid, SIGKILL);
	free_all(&info);
	return (0);
}
