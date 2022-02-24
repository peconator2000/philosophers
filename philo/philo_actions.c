/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:06:02 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 16:20:42 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_unlock(&(ph->info->stop[ph->num]));
	msg("IS EATING", ph, 0, 1);
	time_note(ph, ph->info->time_to_eat);
	pthread_mutex_unlock(&(ph->info->forks[ph->rfork]));
	pthread_mutex_unlock(&(ph->info->forks[ph->lfork]));
	if (ph->eat_num == ph->info->how_eat)
		ph->info->full_num++;
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
	pthread_mutex_lock(&((ph->info->forks)[ph->lfork]));
	if (ph->info->dead || ph->info->phnum == 1)
	{
		pthread_mutex_unlock(&((ph->info->forks)[ph->lfork]));
		return ;
	}
	msg("TAKE LEFT FORK", ph, 0, 0);
	pthread_mutex_lock(&((ph->info->forks)[ph->rfork]));
	pthread_mutex_lock(&(ph->info->stop[ph->num]));
	ph->eating = 1;
	ph->last_eat = gettime();
	if (ph->info->dead)
	{
		pthread_mutex_unlock(&(ph->info->stop[ph->num]));
		pthread_mutex_unlock(&((ph->info->forks)[ph->lfork]));
		pthread_mutex_unlock(&((ph->info->forks)[ph->rfork]));
		return ;
	}
	msg("TAKE RIGTH FORK", ph, 0, 0);
	philo_eat(ph);
	philo_sleep(ph);
}

void	*philo_move(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 == 0)
		usleep(100);
	while (!(philo->info->dead))
		philo_life(philo);
	return (NULL);
}
