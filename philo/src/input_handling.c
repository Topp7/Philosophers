/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:05 by stopp             #+#    #+#             */
/*   Updated: 2024/08/16 16:53:15 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	chk_values(t_philo *philo)
{
	int	status;

	status = 1;
	if (philo->death_time < 10 || philo->eat_time < 10
		|| philo->sleep_time < 10)
	{
		status = 0;
		error_msg("time too small");
	}
	if (philo->meal_amount == 0)
	{
		status = 0;
		error_msg("no meals to eat");
	}
	return (status);
}

t_philo	*save_input(char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->phil_amount = ft_atoi(argv[1]);
	if (philo->phil_amount > 200 || philo->phil_amount < 2)
	{
		error_msg("Invalid amount of philos");
		return (NULL);
	}
	philo->death_time = (u_int64_t)ft_atoi(argv[2]);
	philo->eat_time = (u_int64_t)ft_atoi(argv[3]);
	philo->sleep_time = (u_int64_t)ft_atoi(argv[4]);
	philo->meal_amount = -1;
	if (argv[5])
		philo->meal_amount = ft_atoi(argv[5]);
	philo->dead = 0;
	if (chk_values(philo) == 0)
		return (NULL);
	return (philo);
}

int	chk_input(int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (error_msg("wrong amount if arguments"));
	while (argv[i] && i < 5)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (error_msg("non numeric character in arguments"));
			j++;
		}
		i++;
	}
	return (1);
}
