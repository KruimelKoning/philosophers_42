/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 13:23:12 by lbartels      #+#    #+#                 */
/*   Updated: 2024/05/22 15:25:30 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

struct	s_info;

typedef struct s_philosopher
{
	int				nbr;
	int				meal_count;
	long			last_meal;
	bool			is_dead;
	bool			is_finished;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	dead;
	struct s_info	*info;
}	t_philosopher;

typedef struct s_info
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				finish_count;
	pthread_mutex_t	lock_end;
	pthread_mutex_t	write;
	bool			end;
	bool			start;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_t		observer;
	t_philosopher	*philo;
}	t_info;

void		*routine(void *arg);
void		*observer(void *arg);

int			init(t_info *philo, char **argv, int argc);

bool		take_fork(t_philosopher *philo);
void		drop_fork(t_philosopher *philo);

bool		check_if_end(t_philosopher *philo);
bool		check_if_start(t_philosopher *philo);

long		get_time(void);
void		print(t_philosopher *philo, char *str);

bool		check_args(int argc, char **argv);

void		ft_usleep(int time);
int			ft_atoi(const char *nptr);
void		free_all(t_info info, int fork, int dead);
void		wait_all(t_info info, int wait);

#endif