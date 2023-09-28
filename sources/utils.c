/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:39:06 by lrichard          #+#    #+#             */
/*   Updated: 2021/12/13 19:44:42 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long int	atoi_ovf(const char *nptr)
{
	int	i;
	int	pos;
	int	nb;

	i = 0;
	nb = 0;
	pos = 1;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			pos *= -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		if ((nb == 214748364 && \
			((pos != -1 && nptr[i] == '8') || nptr[i] == '9')) || \
			((nb > 214748364 || nb >= 1000000000)))
			return (2147483648);
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return ((long int)(nb * pos));
}

void	printn(long long n)
{
	char	c;

	if (n >= 10)
		printn(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}

int	isint(char *str)
{
	if (atoi_ovf(str) == 2147483648)
		return (0);
	str--;
	while (*(++str))
		if (*str < 47 || *str > 58)
			return (0);
	return (1);
}

int	nmalloc(void **var, int size)
{
	*var = malloc(size);
	if (!(*var))
		return (0);
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
