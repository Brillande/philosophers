/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 04:49:43 by emedina-          #+#    #+#             */
/*   Updated: 2024/08/05 16:20:51 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_second_fork(t_philo *philo)
{
	is_alive(philo);
	if ((philo->is_dead == 0) && (stop_or_continue(philo, 0) == 0))
	{
		if (philo->philos % 2 == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			philo->lock_r_fork = 1;
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			philo->lock_l_fork = 1;
		}
		print(*philo, msg(FORK, philo->philos));
	}
}
