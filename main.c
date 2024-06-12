/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:33 by stopp             #+#    #+#             */
/*   Updated: 2024/06/12 18:29:52 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(char *str)
{
	printf("%serror: %s%s\n", RED, str, RESET);
	return (0);
}

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
	return (1);
}

int	main(int argc, char *argv[])
{
	struct timeval	end;
	struct timeval	start;

	gettimeofday(&start, NULL);
	if (chk_input(argc, argv) == 0)
		return (1);
	printf("%sinput is fine%s\n", GREEN, RESET);
	gettimeofday(&end, NULL);
	printf("time passed since starting the project: %dms", (end.tv_usec - start.tv_usec) );
}
