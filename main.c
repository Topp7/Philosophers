/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:33 by stopp             #+#    #+#             */
/*   Updated: 2024/06/14 14:35:24 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(char *str)
{
	printf("%serror: %s%s\n", RED, str, RESET);
	return (0);
}

// t_philo	*save_input(char **argv)
// {
// 	int		i;
// 	t_philo	*philo;

// 	i = 0;
// 	(void)argv
// 	philo = malloc(sizeof(t_philo));
// 	if (!philo)
// 		return (NULL);
// }

int	chk_input(int argc, char **argv)
{
	int	i;
	int	j;

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
	// save_input(argv);
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
	// t_philo			data;
	uint64_t	start;
	uint64_t	end;

	start = get_time();
	if (chk_input(argc, argv) == 0)
		return (1);
	printf("%sinput is fine%s\n", GREEN, RESET);
	ft_usleep(10000);
	end = get_time();
	printf("time passed since starting the project: %llums", end - start);
}
