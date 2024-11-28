/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 12:53:35 by lbartels      #+#    #+#                 */
/*   Updated: 2024/05/06 17:59:18 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (write(2, "ERROR invalid args\n", 20), 1);
	if (check_args(argc, argv) == false)
		return (write(2, "ERROR invalid args\n", 20), 1);
	if (init(&info, argv, argc) != 0)
		return (write(2, "ERROR while initializing\n", 26), 1);
	wait_all(info, info.nbr_philo);
	free_all(info, info.nbr_philo, info.nbr_philo);
	return (0);
}
