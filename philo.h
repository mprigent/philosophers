/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:55:08 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/22 14:54:28 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				n;
	int				nb_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	check_mutex;
	pthread_t		thread;
	struct s_conf	*conf;
	struct timeval	last_eat;
}	t_philo;

typedef struct s_conf
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				must_eat;
	int				nb_eat_final;
	int				finish;
	pthread_mutex_t mutex_finish;
	pthread_mutex_t	mutex_final;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	struct timeval	create;
}	t_conf;

long long	ft_atoi(const char *str);
int			ft_strlen(char *str);
void		ft_print_err(char *str);
void		ft_parse(t_conf *conf, int argc, char **argv);
int			ft_check_args(t_conf *conf, int argc);
int			ft_init(t_conf *conf, int argc, char **argv);
int			ft_init_philo(t_conf *conf);
long long	ft_time(struct timeval instant);
void		ft_print_msg(t_philo *philo, char *str);
void		ft_forks(t_philo *philo);
void		ft_thinking(t_philo *philo);
void		ft_sleeping(t_philo *philo);
void		ft_eating(t_philo *philo);
void		*ft_actions(void *argv);
void		*ft_check_must_eat(void *argv);
void		*ft_check_death(void *argv);
void		ft_create_philo(t_conf *conf);
int			ft_malloc(void *dst, size_t size);
void		ft_join(t_conf *conf);
uint64_t	ft_get_time(void);
void		ft_meditate(int time_to_meditate);

#endif
