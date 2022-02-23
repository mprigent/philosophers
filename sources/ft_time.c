/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:32:09 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/23 15:47:06 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	ft_time(struct timeval instant)
{
	long long	ms;

	ms = instant.tv_sec * 1000;
	ms += instant.tv_usec / 1000;
	return (ms);
}

uint64_t	ft_get_time(t_philo *philo)
{
	static struct timeval	tv;
	static int				begining_time;
	uint64_t				ret;

	pthread_mutex_lock(&philo->conf->acces_time);
	if (!begining_time)
	{
		pthread_mutex_unlock(&philo->conf->acces_time);
		gettimeofday(&tv, NULL);
		pthread_mutex_lock(&philo->conf->acces_time);
		begining_time = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000);
		pthread_mutex_unlock(&philo->conf->acces_time);
	}
	pthread_mutex_unlock(&philo->conf->acces_time);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->conf->acces_time);
	ret = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000) - begining_time;
	pthread_mutex_unlock(&philo->conf->acces_time);
	return (ret);
}

void	ft_meditate(int time_to_meditate, t_philo *philo)
{
	uint64_t		instant;
	uint64_t		start_meditation;

	start_meditation = ft_get_time(philo);
	instant = start_meditation;
	while (instant < start_meditation + time_to_meditate)
	{
		usleep(100);
		instant = ft_get_time(philo);
	}
}
