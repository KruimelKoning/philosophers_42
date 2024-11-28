/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:14:11 by lbartels      #+#    #+#                 */
/*   Updated: 2024/05/22 14:48:08 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		usleep(1000);
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	min;

	i = 0;
	num = 0;
	min = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			min = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	if (min == 1)
		num = -num;
	return (num);
}

void	wait_all(t_info info, int wait)
{
	int	i;

	i = 0;
	while (i < wait)
	{
		pthread_join(info.philo[i].thread, NULL);
		i++;
	}
	if (wait == info.nbr_philo && wait != 1)
		pthread_join(info.observer, NULL);
}

void	free_all(t_info info, int fork, int dead)
{
	int	i;

	i = 0;
	while (i < fork)
	{
		pthread_mutex_destroy(&info.forks[i]);
		i++;
	}
	i = 0;
	while (i < dead)
	{
		pthread_mutex_destroy(&info.philo[i].dead);
		i++;
	}
	pthread_mutex_destroy(&info.lock_end);
	pthread_mutex_destroy(&info.write);
	if (info.philo)
		free(info.philo);
	if (info.forks)
		free(info.forks);
}
