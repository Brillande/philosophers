/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:10:27 by emedina-          #+#    #+#             */
/*   Updated: 2024/07/29 05:02:51 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo)
{
	is_alive(philo);
	if ((philo->is_dead == 0) && (stop_or_continue(philo, 0) == 0))
	{
		if (philo->philos % 2 == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			philo->lock_l_fork = 1;
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			philo->lock_r_fork = 1;
		}
		print(*philo, msg(FORK, philo->philos));
	}
	take_second_fork(philo);
}

int	stop_or_continue(t_philo *philo, int flag)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->update);
	if (flag == 1)
	{
		philo->data->stop = 1;
		ret = 1;
	}
	else if (flag == 0)
		ret = philo->data->stop;
	pthread_mutex_unlock(&philo->data->update);
	return (ret);
}

void	eat_pasta(t_philo *philo)
{
	struct timeval	now;

	if ((philo->is_dead == 0) && (stop_or_continue(philo, 0) == 0))
	{
		print(*philo, msg(EAT, philo->philos));
		gettimeofday(&now, NULL);
		philo->dead_of_hungry = add_ms(now, philo->data->die);
		philo->eaten++;
		if ((philo->is_satiated == 0) && (philo->eaten >= philo->data->hungry))
		{
			done(philo, 1);
			philo->is_satiated = 1;
			if (done(philo, 0) == 1)
				stop_or_continue(philo, 1);
		}
		usleep(philo->data->eat * 1000);
		eat_pasta2(philo);
	}
}

void	going_to_sleep(t_philo *philo)
{
	if ((philo->is_dead == 0) && (stop_or_continue(philo, 0) == 0))
	{
		print(*philo, msg(SLEEP, philo->philos));
		usleep(philo->data->sleep * 1000);
		is_alive(philo);
	}
}

void	unlock_first_fork(t_philo *philo)
{
	if (stop_or_continue(philo, 0) == 1 && (philo->lock_l_fork == 1
			|| philo->lock_r_fork == 1))
	{
		if (philo->philos % 2 == 0 && philo->lock_l_fork == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			philo->lock_l_fork = 0;
		}
		else if (philo->philos % 2 == 1 && philo->lock_r_fork == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			philo->lock_r_fork = 0;
		}
	}
	unlock_second_fork(philo);
}
