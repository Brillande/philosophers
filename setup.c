/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:07:15 by emedina-          #+#    #+#             */
/*   Updated: 2024/07/29 05:19:30 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*format(int ac, char **av)
{
	t_data	*dat;

	dat = malloc(sizeof(t_data));
	if (dat == NULL)
	{
		perror("error locating dat\n");
		exit(EXIT_FAILURE);
	}
	check_atoi(ac, av, dat);
	dat->amount_of_philo = ft_atoi(av[1]);
	dat->die = ft_atoi(av[2]);
	dat->eat = ft_atoi(av[3]);
	dat->sleep = ft_atoi(av[4]);
	dat->stop = 0;
	dat->satiated = 0;
	if (ac == 6)
		dat->hungry = ft_atoi(av[5]);
	else
		dat->hungry = -1;
	gettimeofday(&dat->start, NULL);
	pthread_mutex_init(&dat->update, NULL);
	return (dat);
}

t_philo	*setup(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->amount_of_philo);
	if (philo == NULL)
	{
		perror("error locating phil");
		return (NULL);
	}
	while (i < (data->amount_of_philo))
	{
		philo[i].id = 0;
		philo[i].data = data;
		philo[i].philos = i + 1;
		philo[i].eaten = 0;
		philo[i].dead_of_hungry = add_ms(data->start, data->die);
		philo[i].is_dead = 0;
		philo[i].is_satiated = 0;
		philo[i].lock_l_fork = 0;
		philo[i].lock_r_fork = 0;
		philo[i].one_dead = 1;
		i++;
	}
	return (philo);
}

pthread_mutex_t	*create_forks(t_philo *philo, int n)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (forks == NULL)
		return (NULL);
	if (n == 1)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[i];
		return (forks);
	}
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[i + 1];
		i++;
	}
	pthread_mutex_init(&forks[n - 1], NULL);
	philo[n - 1].l_fork = &forks[n - 1];
	philo[n - 1].r_fork = &forks[0];
	return (forks);
}

void	destroy_free(pthread_mutex_t *forks, t_philo *philos, t_data *data)
{
	int	n;
	int	i;

	pthread_mutex_lock(&data->update);
	n = data->amount_of_philo;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_unlock(&data->update);
	pthread_mutex_destroy(&data->update);
	free(forks);
	free(data);
	free(philos);
}
