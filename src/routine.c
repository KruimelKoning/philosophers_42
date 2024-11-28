/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 14:54:56 by lbartels      #+#    #+#                 */
/*   Updated: 2024/05/27 14:14:09 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	print(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->info->write);
	printf("%ld %d %s\n",
		get_time() - philo->info->start_time, philo->nbr, str);
	pthread_mutex_unlock(&philo->info->write);
}

bool	check_philo(t_info *info, int i)
{
	pthread_mutex_lock(&info->philo[i].dead);
	if (info->philo[i].last_meal < (get_time() \
			- info->philo[i].info->start_time) \
			- info->philo[i].info->time_to_die)
	{
		pthread_mutex_lock(&info->lock_end);
		info->end = true;
		print(&info->philo[i], "died");
		pthread_mutex_unlock(&info->lock_end);
		pthread_mutex_unlock(&info->philo[i].dead);
		return (true);
	}
	if (info->philo[i].is_finished == true)
		info->finish_count++;
	pthread_mutex_unlock(&info->philo[i].dead);
	return (false);
}

void	*observer(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	ft_usleep(50);
	while (true)
	{
		i = 0;
		while (i < info->nbr_philo)
		{
			if (check_philo(info, i) == true)
				return (NULL);
			i++;
		}
		if (info->finish_count == info->nbr_philo)
		{
			pthread_mutex_lock(&info->lock_end);
			info->end = true;
			pthread_mutex_unlock(&info->lock_end);
			return (NULL);
		}
		info->finish_count = 0;
		ft_usleep(5);
	}
	return (NULL);
}

void	eat(t_philosopher *philo)
{
	if (take_fork(philo) == false)
		return ;
	print(philo, "is eating");
	pthread_mutex_lock(&philo->dead);
	philo->last_meal = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->dead);
	if (philo->info->time_to_die < philo->info->time_to_eat)
		ft_usleep(philo->info->time_to_die + 20);
	else
		ft_usleep(philo->info->time_to_eat);
	drop_fork(philo);
	philo->meal_count++;
	if (philo->meal_count == 0)
	{
		pthread_mutex_lock(&philo->dead);
		philo->is_finished = true;
		pthread_mutex_unlock(&philo->dead);
	}
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (check_if_start(philo) == false)
		ft_usleep(1);
	print(philo, "is thinking");
	if (philo->info->nbr_philo == 1)
	{
		ft_usleep(philo->info->time_to_die);
		return (print(philo, "died"), NULL);
	}
	if (philo->nbr % 2 != 0)
		ft_usleep(20);
	while (true)
	{
		eat(philo);
		if (check_if_end(philo) == true)
			break ;
		print(philo, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		if (check_if_end(philo) == true)
			break ;
		print(philo, "is thinking");
	}
	return (NULL);
}
