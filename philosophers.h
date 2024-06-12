/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:38 by stopp             #+#    #+#             */
/*   Updated: 2024/06/12 14:26:03 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// header file
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ------------------------------- DEFINITIONS ------------------------------ */

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"

/* -------------------------------- LIBRARIES ------------------------------- */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

/* -------------------------------- STRUCTS --------------------------------- */

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			philo_num;
	int			meal_amount;
	size_t		last_eaten;
	size_t		death_time;
	size_t		eat_time;
	size_t		sleep_time;
	size_t		start_time;

}	t_philo;

/* ------------------------------- FUNCTIONS -------------------------------- */

// ---------------------------------- main -------------------------------------

#endif
