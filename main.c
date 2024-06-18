/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:33 by stopp             #+#    #+#             */
/*   Updated: 2024/06/18 16:45:38 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	forks = data->forks;
	philos = data->philos;
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_mutex_init(&forks[i], NULL);
		philos[i].r_fork = &forks[i];
		if ((i + 1) < data->philo_amount)
			philos[i + 1].l_fork = &forks[i];
		else
			philos[0].l_fork = &forks[i];
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_amount)
	{
		data->philos[i].id = i;
		data->philos[i].times_eaten = 0;
		data->philos[i].last_eaten = 0;
		data->philos[i].start_time = 0;
		data->philos[i].deadlock = &data->deadlock;
		data->philos[i].writelock = &data->writelock;
		data->philos[i].meallock = &data->meallock;
		data->philos[i].times_to_eat = &data->times_to_eat;
		data->philos[i].philo_amount = &data->philo_amount;
		data->philos[i].times_to_eat = &data->times_to_eat;
	}
	init_forks(data);
}

void	phil_routine(t_philo *philos)
{
	if (philos->id % 2 == 1)
		ft_usleep()
	while (1)
	{

	}
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (chk_input(argc, argv) == 0)
		return (1);
	data = save_input(argv);
	if (!data)
		return (1);
	init_philos(data);
}
