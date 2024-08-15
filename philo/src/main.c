/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:33 by stopp             #+#    #+#             */
/*   Updated: 2024/08/15 18:34:29 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	dead_chk(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&philo->mutex->dead);
	if (philo->dead == 1)
		status = 1;
	pthread_mutex_unlock(&philo->mutex->dead);
	return (status);
}

int	observer(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	pthread_mutex_lock(&(philo->mutex->meals));
	if ((curr_time() - philo->last_meal) > (uint64_t)philo->death_time)
	{
		pthread_mutex_unlock(&(philo->mutex->meals));
		while (philo->dead == 0)
		{
			pthread_mutex_lock(&philo->mutex->dead);
			philo->dead = 1;
			pthread_mutex_unlock(&philo->mutex->dead);
			philo = philo->next;
		}
		usleep(3000);
		pthread_mutex_lock(tmp->mutex->print);
		printf("%llu %i  has died\n", (curr_time() - tmp->start_time),
			tmp->id);
		pthread_mutex_unlock(tmp->mutex->print);
		return (1);
	}
	else
		pthread_mutex_unlock(&(philo->mutex->meals));
	return (0);
}

void	*observe_philos(void *tmp)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)tmp;
	i = 0;
	while (1)
	{
		if (observer(philos) == 1)
			break ;
		else if (philos->full == 1)
			i++;
		else
			i = 0;
		if (i == philos->phil_amount)
			break ;
		philos = philos->next;
	}
	return (NULL);
}

int	join_thrds(pthread_t *t_id, int i)
{
	int	status;

	status = 1;
	while (i >= 0)
	{
		if (pthread_join(t_id[i], NULL) != 0)
		{
			printf("thread joining failed\n");
			status = 0;
		}
		i--;
	}
	free (t_id);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_philo			*philo;

	if (chk_input(argc, argv) == 0)
		return (1);
	philo = save_input(argv);
	if (!philo)
		return (1);
	if (init_philos(philo) == 0)
		return (1);
	if (routine_setup(philo) == 0)
		return (1);
	free_all(philo);
	return (0);
}
