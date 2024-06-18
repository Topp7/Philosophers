/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:38 by stopp             #+#    #+#             */
/*   Updated: 2024/06/18 16:44:16 by stopp            ###   ########.fr       */
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
	int				times_eaten;
	uint64_t		last_eaten;
	uint64_t		start_time;
	int				*times_to_eat;
	int				*philo_amount;
	uint64_t		*death_time;
	uint64_t		*eat_time;
	uint64_t		*sleep_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*writelock;
	pthread_mutex_t	*deadlock;
	pthread_mutex_t	*meallock;

}	t_philo;

typedef struct s_data
{
	int				times_to_eat;
	int				philo_amount;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	meallock;
	pthread_mutex_t	writelock;
	pthread_mutex_t	*forks;
	int				dead_flag;
	t_philo			*philos;
	pthread_t		*phil_thrds;
}	t_data;

/* ------------------------------- FUNCTIONS -------------------------------- */

//	time_utils.c
uint64_t	curr_time(void);
void		ft_usleep(uint64_t ms);

//	utils.c
int			error_msg(char *str);
int			ft_atoi(const char *str);

//input_handling.c
int			chk_input(int argc, char **argv);
t_philo		*save_input(char **argv);

// ---------------------------------- main -------------------------------------

#endif
