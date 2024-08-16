/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:45:52 by stopp             #+#    #+#             */
/*   Updated: 2024/08/16 17:43:06 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	error_msg(char *str)
{
	printf("%serror: %s%s\n", RED, str, RESET);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	value;
	int	negative_check;

	value = 0;
	negative_check = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative_check = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - 48);
		str++;
	}
	if (negative_check == 1)
		value *= -1;
	return (value);
}

void	print_status(t_philo *philo, char c)
{
	pthread_mutex_lock(philo->mutex->print);
	philo->curr_time = (curr_time() - philo->start_time);
	if (dead_chk(philo) == 1 || full_chk(philo) == 1)
	{
		pthread_mutex_unlock(philo->mutex->print);
		return ;
	}
	else if (c == 't')
		printf("%llu %i  is thinking\n", philo->curr_time, philo->id);
	else if (c == 'e')
		printf("%llu %i  is eating\n", philo->curr_time, philo->id);
	else if (c == 's')
		printf("%llu %i  is sleeping\n", philo->curr_time, philo->id);
	else if (c == 'f')
		printf("%llu %i  has taken a fork\n", philo->curr_time, philo->id);
	pthread_mutex_unlock(philo->mutex->print);
}

void	free_all(t_philo *philo)
{
	int		i;
	int		phil_amount;
	t_philo	*tmp;

	i = 1;
	pthread_mutex_destroy(philo->mutex->print);
	pthread_mutex_destroy(philo->mutex->full_mtx);
	free(philo->mutex->print);
	free(philo->mutex->full_mtx);
	free(philo->full);
	phil_amount = philo->phil_amount;
	while (i <= phil_amount)
	{
		tmp = philo;
		pthread_mutex_destroy(&(philo->mutex->meals));
		pthread_mutex_destroy(philo->mutex->r_fork);
		free(philo->mutex->r_fork);
		pthread_mutex_destroy(&(philo->mutex->dead));
		free(philo->mutex);
		if (i < philo->phil_amount)
			philo = philo->next;
		free(tmp);
		i++;
	}
}
