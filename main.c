/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:52:06 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/16 14:27:06 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_conf	conf;

	memset(&conf, 0, sizeof(conf));
	if (argc != 5 && argc != 6)
		ft_print_err("wrong arguments");
	if (ft_init(&conf, argc, argv))
		return (1);
	ft_create_philo(&conf);
	ft_join(&conf);
	return (0);
}
