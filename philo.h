/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:55:08 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/13 16:41:16 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_conf
{
	int nb_philo;
	int	time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int must_eat;
}	t_conf;

long long	ft_atoi(const char *str);
static void	ft_parse(t_conf *conf, int argc, char *argv[]);
static int	ft_check_args(t_conf *conf, int argc);
int	ft_init(t_conf *conf, int argc, char *argv[]);

#endif