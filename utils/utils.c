/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:47:07 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/21 13:32:51 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_msg(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	instant;

	pthread_mutex_lock(&philo->conf->mutex_final);
	gettimeofday(&instant, NULL);
	ms = ft_time(instant) - ft_time(philo->conf->create);
	if (!philo->conf->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, str);
	pthread_mutex_unlock(&philo->conf->mutex_final);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (1);
	memset(*(void **)dst, 0, size);
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
}
