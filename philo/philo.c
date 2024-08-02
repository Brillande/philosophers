/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:09:15 by emedina-          #+#    #+#             */
/*   Updated: 2024/08/02 08:11:27 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dining_alone(void *ptr)
{
	t_philo	*philo;

	philo = (((t_philo *)ptr));
	pthread_mutex_lock(philo->l_fork);
	print(*philo, msg(FORK, philo->philos));
	while (stop_or_continue(philo, 0) == 0)
		is_alive(philo);
	pthread_mutex_unlock(philo->l_fork);
}

void	dining_loop(void *ptr)
{
	t_philo	*philo;

	philo = (((t_philo *)ptr));
	while (stop_or_continue(philo, 0) == 0)
	{
		take_first_fork(philo);
		eat_pasta(philo);
		going_to_sleep(philo);
		print(*philo, msg(THINK, philo->philos));
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
}

void	maneage_one_thread(t_philo *philo)
{
	pthread_create(&philo[0].id, NULL, (void *)&dining_alone, &philo[0]);
	pthread_detach(philo[0].id);
	while (stop_or_continue(philo, 0) == 0)
		usleep(1000);
}

void	maneage_mult_thread(t_philo *philo)
{
	int	i;
	int	n;

	i = 0;
	n = (philo->data->amount_of_philo);
	while (i < n)
	{
		pthread_create(&philo[i].id, NULL, (void *)&dining_loop, &philo[i]);
		i++;
	}
	i = 0;
	while (i < n)
		pthread_join(philo[i++].id, NULL);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_data			*data;
	pthread_mutex_t	*forks;

	if (ac == 5 || ac == 6)
	{
		data = format(ac, av);
		philo = setup(data);
		if (philo == NULL)
			philo_null(data);
		forks = create_forks(philo, data->amount_of_philo);
		if (forks == NULL)
			forks_null(data, philo);
		if (data->amount_of_philo == 1)
			maneage_one_thread(philo);
		else
			maneage_mult_thread(philo);
		destroy_free(forks, philo, data);
	}
	else
		printf("only 4 or 5 args");
	return (0);
}
