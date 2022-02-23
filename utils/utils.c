/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:47:07 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/21 16:15:35 by mprigent         ###   ########.fr       */
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}
