/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:37 by soren             #+#    #+#             */
/*   Updated: 2024/08/15 18:20:51 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	philo_sleep(t_philo *philo)
{
	if (dead_chk(philo) == 1 || philo->full == 1)
		return (1);
	print_status(philo, 's');
	ft_usleep((uint64_t)(philo->sleep_time), philo);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (dead_chk(philo) == 1 || philo->full == 1)
		return (1);
	pthread_mutex_lock(philo->mutex->r_fork);
	print_status(philo, 'f');
	pthread_mutex_lock(philo->mutex->l_fork);
	print_status(philo, 'f');
	pthread_mutex_lock(&philo->mutex->meals);
	philo->last_meal = curr_time();
	pthread_mutex_unlock(&philo->mutex->meals);
	print_status(philo, 'e');
	ft_usleep((uint64_t)(philo->eat_time), philo);
	pthread_mutex_unlock(philo->mutex->r_fork);
	pthread_mutex_unlock(philo->mutex->l_fork);
	philo->meal_count++;
	if (philo->meal_amount != -1)
	{
		if (philo->meal_count == philo->meal_amount)
		{
			philo->full = 1;
			return (1);
		}
	}
	return (0);
}

int	philos_think(t_philo *philo)
{
	if (dead_chk(philo) == 1 || philo->full == 1)
		return (1);
	print_status(philo, 't');
	return (0);
}

void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->eat_time / 2, philo);
	while (1)
	{
		if (philos_think(philo) == 1)
			break ;
		if (philo_eat(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
			break ;
	}
	return (NULL);
}

int	routine_setup(t_philo *philo)
{
	pthread_t	*t_id;
	int			i;
	t_philo		*tmp;

	i = 0;
	tmp = philo;
	t_id = malloc(sizeof(pthread_t) * (philo->phil_amount + 1));
	if (!t_id)
		return (0);
	set_start_time(philo);
	while (i < philo->phil_amount)
	{
		if (pthread_create(t_id + i, NULL, phil_routine, tmp) != 0)
			return (join_thrds(t_id, i), 0);
		tmp = tmp->next;
		i++;
	}
	if (pthread_create(&t_id[i], NULL, observe_philos, philo) != 0)
		return (join_thrds(t_id, i), 0);
	if (join_thrds(t_id, i) == 0)
		return (0);
	return (1);
}
