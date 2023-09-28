/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:54:01 by lrichard          #+#    #+#             */
/*   Updated: 2021/12/13 19:29:59 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	int				eff;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	long long		st;
	int				timestoeat;
	int				loop;
	pthread_mutex_t	prin;
	pthread_mutex_t	*forks;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				lf;
	int				rf;
	long long		timeate;
	int				timesate;
	pthread_t		thread;
	pthread_mutex_t	eating;
	t_data			*data;
}				t_philo;

typedef pthread_mutex_t	t_mutex;

void		*lifeloop(void *voidphilo);
void		checkloop(t_philo *philos, t_data *data);
long int	atoi_ovf(const char *nptr);
void		printn(long long n);
int			isint(char *str);
int			nmalloc(void **var, int size);
long long	get_time(void);
void		newsleep(int time, long long calltime);

#endif
