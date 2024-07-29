/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:09:50 by emedina-          #+#    #+#             */
/*   Updated: 2024/07/29 04:25:45 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo philo, t_msg *msg)
{
	struct timeval	now;
	size_t			milli;

	if (stop_or_continue(&philo, 0) == 0)
	{
		pthread_mutex_lock(&philo.data->update);
		gettimeofday(&now, NULL);
		milli = ms_after(msg->event_time, philo.data->start);
		printf("%lu %i ", milli, philo.philos);
		if (msg->state == FORK)
			printf("has taken a fork\n");
		if (msg->state == EAT)
			printf("is eating\n");
		if (msg->state == SLEEP)
			printf("is sleeping\n");
		if (msg->state == THINK)
			printf("is thinking\n");
		if (msg->state == DIE && philo.one_dead == 1)
		{
			printf("died\n");
			philo.one_dead = 0;
		}
		pthread_mutex_unlock(&philo.data->update);
	}
	free(msg);
}

t_msg	*msg(int state, int philos)
{
	t_msg			*msg;
	struct timeval	now;

	msg = malloc(sizeof(t_msg));
	if (!msg)
	{
		perror("error alocating msg");
		exit(EXIT_FAILURE);
	}
	gettimeofday(&now, NULL);
	msg->philo = philos;
	msg->state = state;
	msg->event_time = now;
	return (msg);
}

int	done(t_philo *philo, int flag)
{
	int	ans;

	ans = 0;
	pthread_mutex_lock(&philo->data->update);
	if (flag == 0)
	{
		if ((philo->data->satiated == philo->data->amount_of_philo)
			&& (philo->data->hungry != -1))
			ans = 1;
	}
	else if (flag == 1)
		philo->data->satiated++;
	pthread_mutex_unlock(&philo->data->update);
	return (ans);
}

void	is_alive(t_philo *philo)
{
	struct timeval	now;

	if (stop_or_continue(philo, 0) == 0)
	{
		gettimeofday(&now, NULL);
		if ((philo->is_dead == 0) && (ms_after(now, philo->dead_of_hungry)))
		{
			print(*philo, msg(DIE, philo->philos));
			pthread_mutex_lock(&philo->data->update);
			philo->data->stop = 1;
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->data->update);
		}
	}
}
