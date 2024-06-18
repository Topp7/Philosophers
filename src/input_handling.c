/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:05 by stopp             #+#    #+#             */
/*   Updated: 2024/06/17 17:53:25 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philo_amount);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_amount);
	if (!data->philo_amount)
		return (free(data->philos), 1);
	data->phil_thrds = malloc(sizeof(pthread_t) * data->philo_amount);
	if (!data->phil_thrds)
		return (free(data->philos), free(data->forks), 1);
}

int	save_input(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_amount = ft_atoi(argv[1]);
	if (data->philo_amount > 200)
	{
		error_msg("Number of Philosophers exceeds 200");
		return (NULL);
	}
	data->death_time = (u_int64_t)ft_atoi(argv[2]);
	data->eat_time = (u_int64_t)ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t)ft_atoi(argv[4]);
	data->times_to_eat = -1;
	if (argv[5])
		data->times_to_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&data->deadlock, NULL);
	pthread_mutex_init(&data->meallock, NULL);
	pthread_mutex_init(&data->writelock, NULL);
	if (malloc_data(data) == 1)
		return (NULL);
	data->dead_flag = 0;
	return (data);
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
	printf("%sinput is fine%s\n", GREEN, RESET);
	return (1);
}
