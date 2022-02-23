/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:31:59 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/23 15:52:20 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_check_must_eat(void *argv)
{
	t_conf	*conf;

	conf = argv;
	pthread_mutex_lock(&conf->acces_finish);
	while (!conf->finish)
	{
		pthread_mutex_unlock(&conf->acces_finish);
		pthread_mutex_lock(&conf->mutex_final);
		pthread_mutex_lock(&conf->acces_finish);
		if (conf->nb_eat_final == conf->nb_philo)
			conf->finish = 1;
		pthread_mutex_unlock(&conf->acces_finish);
		pthread_mutex_unlock(&conf->mutex_final);
		pthread_mutex_lock(&conf->acces_finish);
	}
	pthread_mutex_unlock(&conf->acces_finish);
	return (NULL);
}

void	*ft_check_death(void *argv)
{
	t_philo			*philo;
	struct timeval	instant;
	long long		ms;

	philo = argv;
	pthread_mutex_lock(&philo->conf->acces_finish);
	while (!philo->conf->finish)
	{
		pthread_mutex_unlock(&philo->conf->acces_finish);
		pthread_mutex_lock(&philo->check_mutex);
		pthread_mutex_lock(&philo->conf->mutex_final);
		gettimeofday(&instant, NULL);
		ms = ft_time(instant) - ft_time(philo->last_eat);
		gettimeofday(&instant, NULL);
		pthread_mutex_lock(&philo->conf->acces_finish);
		if (ms >= philo->conf->time_to_die && philo->conf->finish == 0)
			ft_check_death2(philo, 0, instant);
		ft_check_death2(philo, 1, instant);
	}
	pthread_mutex_unlock(&philo->conf->acces_finish);
	return (NULL);
}

void	ft_check_death2(t_philo *philo, int i, struct timeval instant)
{
	if (!i)
	{
		pthread_mutex_unlock(&philo->conf->acces_finish);
		printf("%lld\t%d\t %s\n", ft_time(instant)
			- ft_time(philo->conf->create), philo->n + 1,
			"\033[0;31mdied...\033[m");
		pthread_mutex_lock(&philo->conf->acces_finish);
		philo->conf->finish = 1;
		pthread_mutex_unlock(&philo->conf->acces_finish);
	}
	else
	{
		pthread_mutex_unlock(&philo->conf->acces_finish);
		pthread_mutex_unlock(&philo->conf->mutex_final);
		pthread_mutex_unlock(&philo->check_mutex);
		pthread_mutex_lock(&philo->conf->acces_finish);
	}	
}

void	*one_philo(t_philo	*philo)
{
	ft_print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&philo->conf->acces_finish);
	while (!philo->conf->finish)
	{
		pthread_mutex_unlock(&philo->conf->acces_finish);
		pthread_mutex_lock(&philo->conf->acces_finish);
	}
	pthread_mutex_unlock(&philo->conf->acces_finish);
	return (0);
}

void	ft_join(t_conf *conf)
{
	int		i;

	i = 0;
	while (i < conf->nb_philo)
	{
		pthread_join(conf->philo[i].thread, NULL);
		pthread_mutex_destroy(&conf->philo[i++].check_mutex);
	}
	free(conf->philo);
	i = 0;
	while (i < conf->nb_philo)
		pthread_mutex_destroy(&conf->forks[i++]);
	free(conf->forks);
	pthread_mutex_destroy(&conf->acces_finish);
	pthread_mutex_destroy(&conf->acces_time);
}
