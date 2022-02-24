/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:28:08 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 18:28:10 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef time_t			t_ttime;
typedef struct timeval	t_timev;
typedef struct s_info	t_info;

typedef struct s_philo
{
	int			num;
	int			eat_num;
	int			eating;
	long int	last_eat;
	int			dead;
	int			full;
	pid_t		pid;
	t_info		*info;
}				t_philo;

typedef struct s_info
{
	t_philo		*ph;
	sem_t		*stop;
	sem_t		*forks;
	long int	timestart;
	long int	time_to_eat;
	long int	time_to_death;
	long int	time_to_sleep;
	int			curnum;
	int			how_eat;
	int			phnum;
	int			is_static;
	int			dead;
	int			end;
	t_thread	*death_tr;
}				t_info;

int			ft_strlen(char *str);
int			ft_atoi(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			free_all(t_info *info);
long int	gettime(void);
void		msg(char *str, t_philo *ph, int death, int eat);
void		time_manager(t_philo *ph);
void		philo_move(t_philo *philo);
void		philo_life(t_philo *ph);
void		*death_checker(void *info);
int			info_init(t_info *info);
int			info_enter(int argc, char **argv, t_info *info);

#endif