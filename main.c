/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:33 by stopp             #+#    #+#             */
/*   Updated: 2024/07/02 18:37:08 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_philo *philo)
{
	int				i;
	pthread_mutex_t	*forks;
	t_philo			*tmp;

	tmp = philo;
	i = 1;
	forks = malloc(sizeof(pthread_mutex_t) * philo->phil_amount);
	if (!forks)
		return (0);
	while (i <= philo->phil_amount)
	{
		pthread_mutex_init(&forks[i], NULL);
		tmp->mutex->r_fork = &forks[i];
		tmp->next->mutex->l_fork = &forks[i];
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	init_new(t_philo *philo, int i, pthread_mutex_t print_mutex)
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
	pthread_mutex_init(&(new->mutex->dead), NULL);
	pthread_mutex_init(&(new->mutex->meals), NULL);
	new->mutex->print = print_mutex;
	return (1);
}

int	add_philos(t_philo *philo)
{
	int				i;
	t_philo			*tmp;
	pthread_mutex_t	print_mutex;

	i = 1;
	tmp = philo;
	pthread_mutex_init(&print_mutex, NULL);
	philo->mutex->print = print_mutex;
	while (i < philo->phil_amount)
	{
		if (init_new(tmp, i++, print_mutex) == 0)
			return (0);
		tmp = tmp->next;
	}
	tmp->next = philo;
	return (1);
}

int	init_philos(t_philo *philo)
{
	philo->mutex = malloc(sizeof(t_mutex));
	if (!(philo->mutex))
		return (0);
	pthread_mutex_init(&(philo->mutex->dead), NULL);
	pthread_mutex_init(&(philo->mutex->meals), NULL);
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

int	dead_chk(t_philo *philo)
{
	if ((curr_time() - philo->last_meal) > (uint64_t)philo->death_time)
	{
		pthread_mutex_lock(&(philo->mutex->dead));
		philo->dead = 1;
		pthread_mutex_unlock(&(philo->mutex->dead));
		pthread_mutex_lock(&(philo->mutex->print));
		printf("%i %i has died\n", philo->curr_time, philo->id);
		pthread_mutex_lock(&(philo->mutex->print));
		return (1);
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	philo->curr_time = curr_time() - philo->start_time;
	if (dead_chk(philo) == 1 || philo->full == 1)
		return (1);
	pthread_mutex_lock(&(philo->mutex->print));
	printf("%i %i is sleeping\n", philo->curr_time, philo->id);
	pthread_mutex_unlock(&(philo->mutex->print));
	ft_usleep((uint64_t)(philo->sleep_time));
	return (0);
}

int	philo_eat(t_philo *philo)
{
	philo->curr_time = curr_time() - philo->start_time;
	if (dead_chk(philo) == 1 || philo->full == 1)
		return (1);
	philo->last_meal = curr_time();
	pthread_mutex_lock(&(philo->mutex->print));
	pthread_mutex_lock(philo->mutex->l_fork);
	printf("%i %i has taken a fork\n", philo->curr_time, philo->id);
	pthread_mutex_lock(philo->mutex->r_fork);
	printf("%i %i has taken a fork\n", philo->curr_time, philo->id);
	printf("%i %i is eating\n", philo->curr_time, philo->id);
	pthread_mutex_unlock(&(philo->mutex->print));
	ft_usleep((uint64_t)(philo->eat_time));
	philo->meal_count++;
	if (philo->meal_count == philo->meal_amount)
		philo->full = 1;
	return (0);
}

int	philos_think(t_philo *philo)
{
	philo->curr_time = curr_time() - philo->start_time;
	if (dead_chk(philo) == 1 || philo->full == 1)
		return (1);
	pthread_mutex_lock(&(philo->mutex->print));
	printf("%i %i is thinking\n", philo->curr_time, philo->id);
	pthread_mutex_unlock(&(philo->mutex->print));
	return (0);
}

void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep((uint64_t)(philo->eat_time / 2));
	philo->start_time = curr_time();
	while (1)
	{
		if (philo_eat(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
			break ;
		if (philos_think(philo) == 1)
			break ;
	}
	return (NULL);
}

// void	print_status(t_philo *philo, char c)
// {
// 	philo->curr_time = curr_time - philo->start_time;
// 	pthread_mutex_lock(&(philo->mutex->print));
// 	if (c == 't')
// 		printf("%i :%i  is thinking\n", philo->curr_time, philo->id);
// 	else if (c == 'e')
// 		printf("%i :%i  is thinking\n", philo->curr_time, philo->id);
// 	else if (c == 's')
// 		printf("%i :%i  is thinking\n", philo->curr_time, philo->id);
// 	else if (c == 'f')
// 		printf("%i :%i  is thinking\n", philo->curr_time, philo->id);
// 	else if (c == 'd')
// 		printf("%i :%i  is thinking\n", philo->curr_time, philo->id);
// 	pthread_mutex_unlock(&(philo->mutex->print));
// }

int	observer(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(philos->mutex->dead));
	while (philos->dead == 1 && i < philos->phil_amount)
	{
		pthread_mutex_unlock(&(philos->mutex->dead));
		philos = philos->next;
		pthread_mutex_lock(&(philos->mutex->dead));
		philos->dead = 1;
		i++;
	}
	pthread_mutex_unlock(&(philos->mutex->dead));
	if (i > 0)
		return (1);
	else
		return (0);
}

void	*observe_philos(void *tmp)
{
	t_philo	*philos;

	philos = (t_philo *)tmp;
	while (1)
	{
		if (observer(philos) == 1)
			break;
		philos = philos->next;
	}
	return (NULL);
}

int	join_thrds(pthread_t *t_id, int i)
{
	while (i >= 0)
	{
		if (pthread_join(t_id[i--], NULL) != 0)
			return (printf("thread joining failed\n"), 0);
	}
	return (1);
}

int	routine_setup(t_philo *philo)
{
	pthread_t	*t_id;
	int			i;
	t_philo		*tmp;

	i = 0;
	tmp = philo;
	t_id = malloc(sizeof(pthread_t) * philo->phil_amount + 1);
	if (!t_id)
		return (0);
	while (i < philo->phil_amount)
	{
		if (pthread_create(&t_id[i++], NULL, phil_routine, tmp) != 0)
			return (join_thrds(t_id, i), 0);
		tmp = tmp->next;
	}
	if (pthread_create(&t_id[i], NULL, observe_philos, philo) != 0)
		return (join_thrds(t_id, i), 0);
	join_thrds(t_id, i);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo		*philo;

	if (chk_input(argc, argv) == 0)
		return (1);
	philo = save_input(argv);
	if (!philo)
		return (1);
	if (init_philos(philo) == 0)
		return (1);
	if (routine_setup(philo) == 0)
		return (1);
	return (0);
}
