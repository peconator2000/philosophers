/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lib_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:28:40 by vellie            #+#    #+#             */
/*   Updated: 2022/01/20 18:28:42 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int			res;
	long long	max;
	int			len;

	res = 0;
	max = 0;
	len = ft_strlen(str);
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - 48;
		max = max * 10 + *str - 48;
		str++;
		len--;
	}
	if (len > 0)
		return (-1);
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (*s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
