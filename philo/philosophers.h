/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:38 by stopp             #+#    #+#             */
/*   Updated: 2024/08/15 18:20:33 by stopp            ###   ########.fr       */
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
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

/* -------------------------------- STRUCTS --------------------------------- */

typedef struct s_mutex
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	dead;
	pthread_mutex_t	*print;
	pthread_mutex_t	meals;
}					t_mutex;

typedef struct s_philo
{
	int				id;
	int				phil_amount;
	int				sleep_time;
	int				eat_time;
	int				death_time;
	int				meal_amount;
	int				meal_count;
	uint64_t		last_meal;
	int				fork;
	int				dead;
	int				full;
	t_mutex			*mutex;
	struct s_philo	*next;
	uint64_t		start_time;
	uint64_t		curr_time;
}					t_philo;

/* ------------------------------- FUNCTIONS -------------------------------- */

//	time_utils.c
uint64_t	curr_time(void);
void		ft_usleep(uint64_t ms, t_philo *philo);
void		set_start_time(t_philo *philo);

//	utils.c
int			error_msg(char *str);
int			ft_atoi(const char *str);
void		print_status(t_philo *philo, char c);
void		free_all(t_philo *philo);

//	input_handling.c
int			chk_input(int argc, char **argv);
t_philo		*save_input(char **argv);

//	routine.c
int			routine_setup(t_philo *philo);

// philo_setup.c
int			init_philos(t_philo *philo);

//	main.c
int			dead_chk(t_philo *philo);
void		*observe_philos(void *tmp);
int			join_thrds(pthread_t *t_id, int i);

// ---------------------------------- main -------------------------------------

#endif
