/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:02:37 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/20 16:22:12 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_parse(t_conf *conf, int argc, char **argv)
{
	conf->nb_philo = ft_atoi(argv[1]);
	conf->time_to_die = ft_atoi(argv[2]);
	conf->time_to_eat = ft_atoi(argv[3]);
	conf->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		conf->must_eat = ft_atoi(argv[5]);
}

int	ft_check_args(t_conf *conf, int argc)
{
	if (argc == 6 && conf->must_eat <= 0)
		ft_print_err("wrong number of time each philosopher must eat: can't be 0 or less.");
	if (conf->nb_philo < 0)
		ft_print_err("wrong number of philosophers: you can't use less then 0.");
	if (conf->nb_philo > 250)
		ft_print_err("wrong number of philosophers: you can't use more then 250.");
	if (conf->time_to_die < 0)
		ft_print_err("wrong time to die: can't be less than 0.");
	if (conf->time_to_eat < 0)
		ft_print_err("wrong time to eat: can't be less than 0.");
	if (conf->time_to_sleep < 0)
		ft_print_err("wrong time to sleep: can't be less than 0.");
	return (0);
}

int	ft_init_philo(t_conf *conf)
{
	int		i;

	pthread_mutex_init(&conf->mutex_final, NULL);
	if (ft_malloc(&conf->philo, sizeof(t_philo) * conf->nb_philo) || \
		ft_malloc(&conf->forks, sizeof(pthread_mutex_t) * conf->nb_philo))
		ft_print_err("malloc failed");
	i = 0;
	while (i < conf->nb_philo)
	{
		conf->philo[i].n = i;
		pthread_mutex_init(&conf->forks[i], NULL);
		pthread_mutex_init(&conf->philo[i].check_mutex, NULL);
		if (i == 0)
			conf->philo[i].left_fork = &conf->forks[conf->nb_philo - 1];
		else
			conf->philo[i].left_fork = &conf->forks[i - 1];
		conf->philo[i].right_fork = &conf->forks[i];
		conf->philo[i].conf = conf;
		++i;
	}
	return (0);
}

void	ft_create_philo(t_conf *conf)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&conf->create, NULL);
	i = 0;
	while (i < conf->nb_philo)
	{
		conf->philo[i].last_eat = conf->create;
		pthread_create(&conf->philo[i].thread, NULL, \
			ft_actions, &conf->philo[i]);
		pthread_create(&thread, NULL, ft_check_death, &conf->philo[i]);
		pthread_detach(thread);
		++i;
	}
	if (conf->must_eat != 0)
	{
		pthread_create(&thread, NULL, ft_check_must_eat, conf);
		pthread_detach(thread);
	}
}

int	ft_init(t_conf *conf, int argc, char **argv)
{
	ft_parse(conf, argc, argv);
	if (ft_check_args(conf, argc))
		return (1);
	if (ft_init_philo(conf))
		return (1);
	return (0);
}
