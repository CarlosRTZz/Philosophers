/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:22:49 by cortiz            #+#    #+#             */
/*   Updated: 2023/06/05 11:27:49 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define NB_ARG_ERR "Wrong number of arguments"
# define ONLY_NB_ERR "Arguments should only contain numbers"
# define VALID_NB_ERR "Arguments should contain valid numbers"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_philo
{
	int					id;
	int					last_meal;
	int					meal_counters;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					nb_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meal;
	int					start;
	int					is_alive;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		mutex_g;
	pthread_mutex_t		mutex_m;
	pthread_t			*th;
	t_philo				*philo;
}	t_data;

/* Monitoring */
void			monitoring(t_data *data);

/* Free */
void			join_thread(t_data *data);
void			destroy_mutex(t_data *data);
void			free_all(t_data *data);

/* Message */
void			put_message(t_philo *philo, char *msg);

/* Utils */
int				ft_atoi(char *str);
int				ft_error(char *str, int i);
int				ft_isalpha(int c);
void			ft_usleep(int time);

/* Init */
int				init_data(t_data *data, int ac, char **av);
int				init_thread(t_data *data);
int				init_mutex(t_data *data);
int				init_philo(t_data *data);
int				init_all(t_data *data);

/* Routine */
int				current_time(void);
void			*routine(void *dfg);

/* Main */
int				check_errors(char **str);

#endif