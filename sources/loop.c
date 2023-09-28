/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 23:23:58 by lrichard          #+#    #+#             */
/*   Updated: 2021/12/15 19:12:02 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print(t_philo *ph, int status, t_mutex *printing)
{
	pthread_mutex_lock(printing);
	if (ph->data->loop)
	{
		printn(get_time() - ph->data->st);
		write(1, " ", 1);
		printn(ph->id);
		if (status == 1)
			write(1, " has taken a fork\n", 18);
		else if (status == 2)
			write(1, " is eating\n", 11);
		else if (status == 3)
			write(1, " is sleeping\n", 13);
		else if (status == 4)
			write(1, " is thinking\n", 13);
		else
		{
			ph->data->loop = 0;
			write(1, " died\n", 6);
		}
	}
	pthread_mutex_unlock(printing);
}

void	newsleep(int time, long long calltime)
{
	while (get_time() - calltime < time)
		usleep(50);
}

void	*lifeloop(void *voidphilo)
{
	t_philo	*ph;

	ph = (t_philo *)voidphilo;
	while (ph->data->loop)
	{
		pthread_mutex_lock(&(ph->data->forks[ph->lf]));
		print(ph, 1, &(ph->data->prin));
		if (ph->data->eff == 1)
			return (0);
		pthread_mutex_lock(&(ph->data->forks[ph->rf]));
		print(ph, 1, &(ph->data->prin));
		pthread_mutex_lock(&(ph->eating));
		pthread_mutex_unlock(&(ph->eating));
		print(ph, 2, &(ph->data->prin));
		ph->timeate = get_time();
		newsleep(ph->data->timetoeat, get_time());
		pthread_mutex_unlock(&(ph->data->forks[ph->lf]));
		pthread_mutex_unlock(&(ph->data->forks[ph->rf]));
		ph->timesate++;
		print(ph, 3, &(ph->data->prin));
		newsleep(ph->data->timetosleep, get_time());
		print(ph, 4, &(ph->data->prin));
	}
	return (0);
}

void	checkloop(t_philo *philos, t_data *data)
{
	int	i;
	int	allfed;

	while (data->loop)
	{
		i = -1;
		allfed = 1;
		while (++i < data->eff)
		{
			pthread_mutex_lock(&(philos[i].eating));
			if (get_time() - philos[i].timeate >= data->timetodie)
			{
				print(&(philos[i]), 0, &(data->prin));
				pthread_mutex_unlock(&(philos[i].eating));
				return ;
			}
			pthread_mutex_unlock(&(philos[i].eating));
			if (philos[i].timesate < data->timestoeat || !data->timestoeat)
				allfed = 0;
		}
		if (allfed)
			data->loop = 0;
	}
}
