/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 17:25:22 by lbartels      #+#    #+#                 */
/*   Updated: 2024/03/05 17:25:23 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

bool	ft_atol(char *str)
{
	long	num;
	int		i;
	long	min;

	num = 0;
	i = 0;
	min = 1;
	if (ft_strlen(str) > 11)
		return (false);
	while (str[i])
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	num = num * min;
	if (num > INT_MAX || num < INT_MIN)
		return (false);
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!argv[i][0])
			return (false);
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (false);
			j++;
		}
		if (ft_atol(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

// && !(((argv[i][j] == '-' || argv[i][j] == '+') && !j))