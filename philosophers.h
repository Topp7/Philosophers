/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:38 by stopp             #+#    #+#             */
/*   Updated: 2024/06/14 17:12:12 by stopp            ###   ########.fr       */
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
	pthread_t		thread;
	int				id;
	int				philo_num;
	int				times_eaten;
	int				times_to_eat;
	size_t			last_eaten;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*writelock;
	pthread_mutex_t	*deadlock;
	pthread_mutex_t	*meallock;

}	t_philo;

typedef struct s_flags
{
	pthread_mutex_t	deadlock;
	pthread_mutex_t	meallock;
	pthread_mutex_t	writelock;
	int				dead_flag;
	t_philo			*philos;
}	t_flags;

/* ------------------------------- FUNCTIONS -------------------------------- */

// ---------------------------------- main -------------------------------------

#endif
