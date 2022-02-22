/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:51:55 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/22 14:56:36 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	ft_print_msg(philo, "has taken a fork");
}

void	ft_thinking(t_philo *philo)
{
	ft_print_msg(philo, "is thinking");
}

void	ft_sleeping(t_philo *philo)
{
	ft_print_msg(philo, "is sleeping");
	ft_meditate(philo->conf->time_to_sleep);
}

void	ft_eating(t_philo *philo)
{
	long long	ms;

	pthread_mutex_lock(&philo->check_mutex);
	gettimeofday(&philo->last_eat, NULL);
	ms = ft_time(philo->last_eat) - ft_time(philo->conf->create);
	pthread_mutex_lock(&philo->conf->mutex_final);
	pthread_mutex_lock(&philo->conf->mutex_finish);
	//mutex_lock(*);
	if (!philo->conf->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, "is eating");
	//mutex_unlock(*);
	pthread_mutex_unlock(&philo->conf->mutex_finish);	
	philo->nb_eat += 1;
	if (philo->nb_eat == philo->conf->must_eat)
		philo->conf->nb_eat_final += 1;
	pthread_mutex_unlock(&philo->conf->mutex_final);
	ft_meditate(philo->conf->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->check_mutex);
}

void	*ft_actions(void *argv)
{
	t_philo	*philo;

	philo = argv;
	if (philo->n % 2 == 0)
		ft_meditate(philo->conf->time_to_eat);
	pthread_mutex_lock(&philo->conf->mutex_finish);
	//mutex_lock(*);
	while (!philo->conf->finish)
	{
		pthread_mutex_unlock(&philo->conf->mutex_finish);
		//mutex_unlock(*);
		ft_forks(philo);
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
		pthread_mutex_lock(&philo->conf->mutex_finish);
		//mutex_lock(*);
	}
	pthread_mutex_unlock(&philo->conf->mutex_finish);
	//mutex_unlock(*);
	return (NULL);
}
