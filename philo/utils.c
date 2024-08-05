/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:06:31 by emedina-          #+#    #+#             */
/*   Updated: 2024/08/05 16:48:17 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timeval_to_ms(struct timeval t)
{
	size_t	milliseconds;

	milliseconds = 0;
	milliseconds += t.tv_sec * 1000;
	milliseconds += t.tv_usec / 1000;
	return (milliseconds);
}

struct timeval	ms_to_timeval(size_t t)
{
	struct timeval	ret_time;

	ret_time.tv_sec = t / 1000;
	ret_time.tv_usec = (t % 1000) * 1000;
	return (ret_time);
}

size_t	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (ft_strlen (str) == 0)
	{
		printf("only possitive numbers");
		return (-2);
	}
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
	}
	if ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
	{
		printf("only possitive numbers");
		return (-2);
	}
	return (result);
}

size_t	ms_after(struct timeval t1, struct timeval t2)
{
	size_t	ms1;
	size_t	ms2;
	size_t	tmp1;
	size_t	tmp2;

	if (t1.tv_sec < t2.tv_sec)
		return (0);
	ms1 = (t1.tv_sec) * 1000;
	ms2 = (t2.tv_sec) * 1000;
	tmp1 = t1.tv_usec / 1000;
	tmp2 = t2.tv_usec / 1000;
	ms1 = ms1 + tmp1;
	ms2 = ms2 + tmp2;
	if (ms1 < ms2)
		return (0);
	else
		return (ms1 - ms2);
}

struct timeval	add_ms(struct timeval t1, size_t ms)
{
	struct timeval	t2;

	t2.tv_sec = t1.tv_sec + (ms / 1000);
	t2.tv_usec = t1.tv_usec + ((ms % 1000) * 1000);
	return (t2);
}
