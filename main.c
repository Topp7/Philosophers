/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:33 by stopp             #+#    #+#             */
/*   Updated: 2024/06/21 17:28:49 by stopp            ###   ########.fr       */
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
		i++;
	}
}

void	init_philos(t_philo *philo)
{
	int	i;

	i = 0;
	philo->last_meal = 0;
	philo->fork = 0;
	philo->dead = 0;
	philo->full = 0;
	philo->mutex = 
	init_forks(data);
}

int	chk_philos(t_philo *philos)
{
	if (*philos->dead_flag == 1)
		return (1);
	else
		return (0);
}

int	philo_died(t_philo *philos, uint64_t timestamp)
{
	if ((timestamp - philos->last_eaten) > *philos->death_time)
	{
		*philos->dead_flag = 1;
		printf("%lld %i has died\n",
			(timestamp - philos->start_time), philos->id);
		return (1);
	}
	return (0);
}

int	philo_sleep(t_philo *philos)
{
	uint64_t	timestamp;

	timestamp = curr_time() - (*philos).start_time;
	if (philo_died(philos, timestamp) == 1)
		return (1);
	pthread_mutex_lock(philos->printlock);
	printf("%lld %i is sleeping\n", timestamp, philos->id);
	pthread_mutex_unlock(philos->printlock);
	ft_usleep(*philos->sleep_time);
	return (0);
}

int	philo_eat(t_philo *philos)
{
	uint64_t	timestamp;

	timestamp = curr_time() - philos->start_time;
	if (philo_died(philos, timestamp) == 1)
		return (1);
	printf("%i, %i\n", philos->times_eaten, *philos->times_to_eat);
	if (philos->times_eaten >= *philos->times_to_eat)
		return (1);
	philos->last_eaten = timestamp;
	printf("3\n");
	pthread_mutex_lock(philos->printlock);
	pthread_mutex_lock(philos->r_fork);
	printf("%lld %i has taken a fork\n", timestamp, philos->id);
	pthread_mutex_lock(philos->l_fork);
	printf("%lld %i has taken a fork\n", timestamp, philos->id);
	printf("%lld %i is eating\n", timestamp, philos->id);
	pthread_mutex_unlock(philos->printlock);
	pthread_mutex_unlock(philos->r_fork);
	pthread_mutex_unlock(philos->l_fork);
	philos->times_eaten++;
	return (0);
}

int	philos_think(t_philo *philos)
{
	uint64_t	timestamp;

	timestamp = curr_time() - philos->start_time;
	if (philo_died(philos, timestamp) == 1)
		return (1);
	pthread_mutex_lock(philos->printlock);
	printf("%lld %i is thinking\n", timestamp, philos->id);
	pthread_mutex_unlock(philos->printlock);
	return (0);
}

void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(*(philo->eat_time) / 2);
	philo->start_time = curr_time();
	while (1)
	{
		if (chk_philos(philo) == 1)
			break ;
		if (philo_eat(philo) == 1)
			break ;
		if (chk_philos(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
			break ;
		if (chk_philos(philo) == 1)
			break ;
		if (philos_think(philo) == 1)
			break ;
	}
	pthread_join(philo->thread, NULL);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	int		i;

	if (chk_input(argc, argv) == 0)
		return (1);
	philo = save_input(argv);
	if (!philo)
		return (1);
	init_philos(philo);
	i = 0;
	while (i < data->philo_amount)
	{
		printf("%i\n", data->philo_amount);
		pthread_create(&(data->phil_thrds[i]), NULL, phil_routine, &philos[i]);
		printf("%i\n", i);
		i++;
	}
	return (0);
}
