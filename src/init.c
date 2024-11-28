/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:18:09 by lbartels      #+#    #+#                 */
/*   Updated: 2024/05/22 17:01:47 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

bool	init_forks(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbr_philo);
	if (!info->forks)
		return (free_all(*info, 0, 0), false);
	i = 0;
	while (i < info->nbr_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (free_all(*info, i, 0), false);
		i++;
	}
	info->philo[0].l_fork = &info->forks[0];
	info->philo[0].r_fork = &info->forks[info->nbr_philo - 1];
	i = 1;
	while (i < info->nbr_philo)
	{
		info->philo[i].l_fork = &info->forks[i];
		info->philo[i].r_fork = &info->forks[i - 1];
		i++;
	}
	return (true);
}

bool	safe_pthread_create(t_info *info, int i)
{
	if (pthread_create(&info->philo[i].thread, NULL,
			&routine, &info->philo[i]) != 0)
	{
		pthread_mutex_lock(&info->lock_end);
		info->end = true;
		info->start = true;
		pthread_mutex_unlock(&info->lock_end);
		wait_all(*info, i);
		return (false);
	}
	return (true);
}

bool	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->end = false;
	info->start = false;
	info->finish_count = 0;
	while (i < info->nbr_philo)
	{
		info->philo[i].nbr = i + 1;
		info->philo[i].info = info;
		info->philo[i].last_meal = 0;
		info->philo[i].is_dead = false;
		info->philo[i].is_finished = false;
		info->philo[i].meal_count = info->nbr_of_meals * -1;
		if (pthread_mutex_init(&info->philo[i].dead, NULL) != 0)
			return (free_all(*info, info->nbr_philo, i), false);
		if (safe_pthread_create(info, i) == false)
			return (free_all(*info, info->nbr_philo, i), false);
		i++;
	}
	pthread_mutex_lock(&info->lock_end);
	info->start_time = get_time();
	info->start = true;
	pthread_mutex_unlock(&info->lock_end);
	return (true);
}

int	init(t_info *info, char **argv, int argc)
{
	info->nbr_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->nbr_of_meals = ft_atoi(argv[5]);
	else
		info->nbr_of_meals = -1;
	info->forks = NULL;
	if (pthread_mutex_init(&info->lock_end, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (pthread_mutex_destroy(&info->lock_end), 1);
	info->philo = malloc(sizeof(t_philosopher) * info->nbr_philo);
	if (!info->philo)
		return (free_all(*info, 0, 0), 2);
	if (!init_forks(info))
		return (3);
	if (!init_philo(info))
		return (4);
	if (info->nbr_philo == 1)
		return (0);
	if (pthread_create(&info->observer, NULL, observer, info) != 0)
		return (free_all(*info, info->nbr_philo, info->nbr_philo), 5);
	return (0);
}
