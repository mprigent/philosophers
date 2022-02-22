/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:47:07 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/22 14:58:32 by mprigent         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->conf->mutex_finish);
	//mutex_lock(*);
	if (!philo->conf->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, str);
	pthread_mutex_unlock(&philo->conf->mutex_finish);
	//mutex_unlock(*);
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
