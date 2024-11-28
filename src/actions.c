/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 14:02:21 by lbartels      #+#    #+#                 */
/*   Updated: 2024/05/27 14:00:59 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

bool	take_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	if (check_if_end(philo) == true)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	print(philo, "has taken a fork");
	return (true);
}

void	drop_fork(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

bool	check_if_end(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->info->lock_end);
	if (philo->info->end == true)
	{
		pthread_mutex_unlock(&philo->info->lock_end);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->lock_end);
	return (false);
}

bool	check_if_start(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->info->lock_end);
	if (philo->info->start == true)
	{
		pthread_mutex_unlock(&philo->info->lock_end);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->lock_end);
	return (false);
}
