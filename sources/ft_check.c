/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:31:59 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/20 20:53:06 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_check_must_eat(void *argv)
{
	t_conf	*conf;

	conf = argv;
	while (!conf->finish)
	{
		pthread_mutex_lock(&conf->mutex_final);
		if (conf->nb_eat_final == conf->nb_philo)
			conf->finish = 1;
		pthread_mutex_unlock(&conf->mutex_final);
	}
	return (NULL);
}

void	*ft_check_death(void *argv)
{
	t_philo			*philo;
	struct timeval	instant;
	long long		ms;

	philo = argv;
	while (!philo->conf->finish)
	{
		pthread_mutex_lock(&philo->check_mutex);
		pthread_mutex_lock(&philo->conf->mutex_final);
		gettimeofday(&instant, NULL);
		ms = ft_time(instant) - ft_time(philo->last_eat);
		gettimeofday(&instant, NULL);
		if (ms >= philo->conf->time_to_die && philo->conf->finish == 0)
		{
			printf("%lld\t%d\t %s\n", ft_time(instant) - ft_time(philo->conf->create), philo->n + 1, "died");
			philo->conf->finish = 1;
		}
		pthread_mutex_unlock(&philo->conf->mutex_final);
		pthread_mutex_unlock(&philo->check_mutex);
	}
	return (NULL);
}
