/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:27:58 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 18:28:01 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	time_note(t_philo *ph, long int time)
{
	long int	cur;
	long int	end;

	cur = gettime();
	end = cur + time;
	while (!(ph->info->dead) && cur < end)
	{
		usleep(100);
		cur = gettime();
	}
}

void	philo_eat(t_philo *ph)
{
	ph->eat_num++;
	msg("IS EATING", ph, 0, 1);
	time_note(ph, ph->info->time_to_eat);
	sem_post(ph->info->forks);
	sem_post(ph->info->forks);
	if (ph->eat_num == ph->info->how_eat)
	{
		ph->info->dead = 1;
		ph->full = 1;
	}
	ph->eating = 0;
}

void	philo_sleep(t_philo *ph)
{
	long int	max_sleep_time;

	if (ph->info->dead)
		return ;
	max_sleep_time = ph->last_eat + ph->info->time_to_death - gettime();
	msg("IS SLEEPING", ph, 0, 0);
	time_note(ph, max_sleep_time);
	msg("IS THINKING", ph, 0, 0);
}

void	philo_life(t_philo *ph)
{
	sem_wait(ph->info->forks);
	if (ph->info->dead || ph->info->phnum == 1)
	{
		sem_post(ph->info->forks);
		return ;
	}
	msg("TAKE LEFT FORK", ph, 0, 0);
	sem_wait(ph->info->forks);
	ph->eating = 1;
	ph->last_eat = gettime();
	if (ph->info->dead)
	{
		sem_post(ph->info->forks);
		sem_post(ph->info->forks);
		return ;
	}
	msg("TAKE RIGTH FORK", ph, 0, 0);
	philo_eat(ph);
	philo_sleep(ph);
}

void	philo_move(t_philo *philo)
{
	if (philo->info->phnum == 1)
		return ;
	if (philo->num % 2 == 0)
		usleep(100);
	while (!(philo->info->dead))
		philo_life(philo);
}
