/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:44:19 by stopp             #+#    #+#             */
/*   Updated: 2024/08/16 17:39:00 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	full_chk(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(philo->mutex->full_mtx);
	if (*(philo->full) == philo->phil_amount)
		status = 1;
	pthread_mutex_unlock(philo->mutex->full_mtx);
	return (status);
}

uint64_t	curr_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	set_start_time(t_philo *philo)
{
	uint64_t	start;

	start = curr_time();
	while (philo->id < philo->next->id)
	{
		philo->start_time = start;
		philo = philo->next;
	}
	philo->start_time = start;
}

void	ft_usleep(uint64_t ms, t_philo *philo)
{
	uint64_t	start;
	int			remain;
	int			elapsed;

	start = curr_time();
	while ((curr_time() - start) < ms)
	{
		if (dead_chk(philo) || *(philo->full) == philo->phil_amount)
			return ;
		elapsed = curr_time() - start;
		remain = (ms - elapsed);
		if (remain > 1)
			usleep((remain / 2) * 1000);
		else
			while ((curr_time() - start) < ms)
				;
	}
}
