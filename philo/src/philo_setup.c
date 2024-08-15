/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:46:13 by soren             #+#    #+#             */
/*   Updated: 2024/08/15 16:22:15 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	init_forks(t_philo *philo)
{
	int				i;
	t_philo			*tmp;
	pthread_mutex_t	*forks;

	tmp = philo;
	i = 0;
	while (i < philo->phil_amount)
	{
		forks = malloc(sizeof(pthread_mutex_t));
		if (!forks)
			return (0);
		pthread_mutex_init(forks, NULL);
		tmp->mutex->r_fork = forks;
		tmp->next->mutex->l_fork = forks;
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	init_new(t_philo *philo, int i)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (0);
	new->mutex = malloc(sizeof(t_mutex));
	if (!(new->mutex))
		return (0);
	new->id = i + 1;
	new->phil_amount = philo->phil_amount;
	new->sleep_time = philo->sleep_time;
	new->eat_time = philo->sleep_time;
	new->death_time = philo->death_time;
	new->meal_amount = philo->meal_amount;
	new->meal_count = philo->meal_count;
	new->last_meal = philo->last_meal;
	new->fork = philo->last_meal;
	new->dead = philo->dead;
	new->full = philo->full;
	philo->next = new;
	pthread_mutex_init(&(new->mutex->meals), NULL);
	return (1);
}

int	add_philos(t_philo *philo)
{
	int				i;
	t_philo			*tmp;
	pthread_mutex_t	*print_mutex;

	i = 1;
	tmp = philo;
	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!print_mutex)
		return (0);
	pthread_mutex_init(print_mutex, NULL);
	philo->mutex->print = print_mutex;
	while (i < philo->phil_amount)
	{
		if (init_new(tmp, i++) == 0)
			return (0);
		tmp = tmp->next;
		tmp->mutex->print = print_mutex;
		tmp->mutex->dead = philo->mutex->dead;
	}
	tmp->next = philo;
	return (1);
}

int	init_philos(t_philo *philo)
{
	philo->mutex = malloc(sizeof(t_mutex));
	if (!(philo->mutex))
		return (0);
	pthread_mutex_init(&philo->mutex->dead, NULL);
	pthread_mutex_init(&philo->mutex->meals, NULL);
	philo->id = 1;
	philo->meal_count = 0;
	philo->last_meal = curr_time();
	philo->fork = 0;
	philo->dead = 0;
	philo->full = 0;
	philo->curr_time = 0;
	if (add_philos(philo) == 0)
		return (0);
	if (init_forks(philo) == 0)
		return (0);
	return (1);
}
