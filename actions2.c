/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 04:49:43 by emedina-          #+#    #+#             */
/*   Updated: 2024/07/29 05:03:59 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_second_fork(t_philo *philo)
{
	if (stop_or_continue(philo, 0) == 1 && philo->is_dead == 0
		&& (philo->lock_l_fork == 1 || philo->lock_r_fork == 1))
	{
		if (philo->philos % 2 == 0 && philo->lock_r_fork == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			philo->lock_r_fork = 0;
		}
		else if (philo->philos % 2 == 1 && philo->lock_l_fork == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			philo->lock_l_fork = 0;
		}
	}
}

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
	unlock_first_fork(philo);
}

void	eat_pasta2(t_philo *philo)
{
	if (philo->lock_l_fork == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		philo->lock_l_fork = 0;
	}
	if (philo->lock_r_fork == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		philo->lock_r_fork = 0;
	}
}
