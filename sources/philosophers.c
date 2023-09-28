/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:12:57 by lrichard          #+#    #+#             */
/*   Updated: 2021/12/13 19:50:41 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	throwerror(char *message)
{
	while (*message)
		write(2, message++, 1);
	return (0);
}

void	free_all(t_philo *philos, t_data *data)
{
	int	i;

	pthread_mutex_destroy(&(data->prin));
	i = -1;
	if (data->forks)
		while (++i < data->eff)
			pthread_mutex_destroy(&(data->forks[i]));
	free(philos);
	free(data->forks);
}

int	init(t_data *data, t_philo **philos, t_mutex **forks)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * data->eff);
	*forks = (t_mutex *)malloc(sizeof(t_mutex) * data->eff);
	data->forks = *forks;
	if (!*philos || !*forks)
		return (throwerror("Memory allocation failed\n"));
	data->loop = (data->eff != 0);
	i = -1;
	while (++i < data->eff)
	{
		(*philos)[i].data = data;
		(*philos)[i].id = i + 1;
		(*philos)[i].lf = i;
		(*philos)[i].rf = (i + 1) % data->eff;
		(*philos)[i].timesate = 0;
		pthread_mutex_init(&((*philos)[i].eating), 0);
	}
	i = -1;
	while (++i < data->eff)
		pthread_mutex_init(&((data->forks)[i]), 0);
	pthread_mutex_init(&(data->prin), 0);
	data->st = get_time();
	return (1);
}

int	getdata(int ac, char **av, t_data *data)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (throwerror("Wrong number of arguments\n"));
	i = 0;
	while (++i < ac)
	{
		if (!isint(av[i]))
			return (throwerror("All arguments should fit in an integer\n"));
		if (atoi_ovf(av[i]) < 0)
			return (throwerror("All arguments should be positive numbers\n"));
		if (i == 1)
			data->eff = atoi_ovf(av[i]);
		else if (i == 2)
			data->timetodie = atoi_ovf(av[i]);
		else if (i == 3)
			data->timetoeat = atoi_ovf(av[i]);
		else if (i == 4)
			data->timetosleep = atoi_ovf(av[i]);
		else if (i == 5)
			data->timestoeat = atoi_ovf(av[i]);
	}
	if (ac == 5)
		data->timestoeat = 0;
	return (1);
}

int	main(int ac, char **av)
{
	int					i;
	t_data				data;
	t_philo				*philos;
	pthread_mutex_t		*forks;

	philos = 0;
	data.forks = 0;
	if (!getdata(ac, av, &data) || !init(&data, &philos, &forks))
	{
		free_all(philos, &data);
		return (0);
	}
	i = -1;
	while (++i < data.eff)
	{
		pthread_create(&(philos[i].thread), 0, &lifeloop, (void *)&(philos[i]));
		philos[i].timeate = data.st;
		newsleep(1, get_time());
	}
	checkloop(philos, &data);
	i = data.eff;
	while (i--)
		pthread_join(philos[i].thread, 0);
	free_all(philos, &data);
	return (0);
}
