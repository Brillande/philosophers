/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:07:36 by emedina-          #+#    #+#             */
/*   Updated: 2024/08/02 08:17:02 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

typedef enum e_monitoring
{
	NONE,
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}					t_monitoring;

typedef struct s_data
{
	size_t			die;
	size_t			sleep;
	size_t			eat;
	int				amount_of_philo;
	int				hungry;
	int				satiated;
	int				stop;
	int				one_dead;
	pthread_mutex_t	update;
	struct timeval	start;
}					t_data;

typedef struct s_philo
{
	t_data			*data;
	int				philos;
	pthread_t		id;
	int				eaten;
	int				is_dead;
	int				is_satiated;
	struct timeval	dead_of_hungry;
	int				lock_l_fork;
	int				lock_r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_msg
{
	int				state;
	struct timeval	event_time;
	int				philo;
}					t_msg;

pthread_mutex_t		*create_forks(t_philo *philo, int n);
t_philo				*setup(t_data *data);
t_data				*format(int ac, char **av);
void				destroy_free(pthread_mutex_t *forks,
						t_philo *philos,
						t_data *data);
void				maneage_one_thread(t_philo *philo);
void				dining_alone(void *ptr);
void				maneage_mult_thread(t_philo *philo);
void				eat_pasta2(t_philo *philo);
void				multiple_philo(void *ptr);
void				unlock_second_fork(t_philo *philo);
size_t				ft_atoi(char *str);
void				take_second_fork(t_philo *philo);
size_t				timeval_to_ms(struct timeval t);
struct timeval		ms_to_timeval(size_t t);
void				check_atoi(int ac, char **av, t_data *dat);
void				unlock_first_fork(t_philo *philo);
void				is_alive(t_philo *philo);
int					stop_or_continue(t_philo *philo, int flag);
void				take_first_fork(t_philo *philo);
void				philo_null(t_data *data);
void				eat_pasta(t_philo *philo);
void				going_to_sleep(t_philo *philo);
size_t				ms_after(struct timeval t1, struct timeval t2);
struct timeval		add_ms(struct timeval t1, size_t ms);
t_msg				*msg(int state, int philos);
void				forks_null(t_data *data, t_philo *philo);
void				print(t_philo philo, t_msg *msg);
int					done(t_philo *philo, int flag);

#endif
