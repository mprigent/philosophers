/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:02:37 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/13 16:42:50 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_parse(t_conf *conf, int argc, char *argv[])
{
	conf->nb_philo = ft_atoi(argv[1]);
	conf->time_to_die = ft_atoi(argv[2]);
	conf->time_to_eat = ft_atoi(argv[3]);
	conf->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		conf->must_eat = ft_atoi(argv[5]);
}

static int	ft_check_args(t_conf *conf, int argc)
{
	if (argc == 6 && conf->must_eat <= 0)
		ft_print_err("wrong number of must eat.");
	if (conf->nb_philo < 0)
		ft_print_err("wrong number of philosophers: you can't use less then 0.");
	if (conf->nb_philo > 250)
		ft_print_err("wrong number of philosophers: you can't use more then 250.");
	if (conf->time_to_die < 0)
		ft_print_err("wrong time to die.");
	if (conf->time_to_eat < 0)
		ft_puterror("wrong time to eat.");
	if (conf->time_to_sleep < 0)
		ft_print_err("wrong time to sleep.");
	return (0);
}

int	ft_init(t_conf *conf, int argc, char *argv[])
{
	ft_parse(conf, argc, argv);
	if (check_info(conf, argc))
		return (1);
	return (0);
}
