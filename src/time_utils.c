/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:44:19 by stopp             #+#    #+#             */
/*   Updated: 2024/07/03 16:04:20 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

uint64_t	curr_time(void)
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
	start = curr_time();
	while (dif < ms)
		dif = curr_time() - start;
}
