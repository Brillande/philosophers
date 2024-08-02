/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 04:33:56 by emedina-          #+#    #+#             */
/*   Updated: 2024/07/29 05:18:49 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_null(t_data *data)
{
	free(data);
	exit(EXIT_FAILURE);
}

void	forks_null(t_data *data, t_philo *philo)
{
	free(data);
	free(philo);
	perror("error locating forks");
	exit(EXIT_FAILURE);
}

void	check_atoi(int ac, char **av, t_data *dat)
{
	int		j;
	size_t	i;

	i = -2;
	j = 1;
	while (j < ac)
	{
		if (ft_atoi(av[j]) == i)
		{
			free(dat);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}
