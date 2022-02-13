/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:21:34 by mprigent          #+#    #+#             */
/*   Updated: 2022/02/13 16:31:11 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_error(char *str)
{
	write(1, "\033[31mError\033[00m\n", 17);
	write (1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(0);
}