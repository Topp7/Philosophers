/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:45:52 by stopp             #+#    #+#             */
/*   Updated: 2024/06/15 13:47:36 by stopp            ###   ########.fr       */
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
