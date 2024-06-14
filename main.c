/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:33 by stopp             #+#    #+#             */
/*   Updated: 2024/06/14 17:12:56 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_philo	*save_input(char **argv)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_num = ft_atoi(argv[1]);
	if (philo->philo_num > 200)
	{
		error_msg("Number of Philosophers exceeds 200");
		return (NULL);
	}
	philo->death_time = ft_atoi(argv[2]);
	philo->eat_time = ft_atoi(argv[3]);
	philo->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		philo->times_to_eat = ft_atoi(argv[5]);
	else
		philo->times_to_eat = -1;
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

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	ft_usleep(uint64_t ms)
{
	uint64_t	start;
	uint64_t	dif;

	dif = 0;
	start = get_time();
	while (dif < ms)
		dif = get_time() - start;
}

int	main(int argc, char *argv[])
{
	t_philo	*inital_philo;

	if (chk_input(argc, argv) == 0)
		return (1);
	inital_philo = save_input(argv);
	if (!inital_philo)
		return (1);
	printf("%sinput is fine%s\n", GREEN, RESET);

}
