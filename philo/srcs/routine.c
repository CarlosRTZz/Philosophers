/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:27:00 by cortiz            #+#    #+#             */
/*   Updated: 2023/06/05 15:14:25 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	int	start;

	start = current_time();
	while ((current_time() - start) < time)
		usleep(100);
}

int	init_diner(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	put_message(philo, FORK);
	if (philo->data->nb_of_philo == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	put_message(philo, FORK);
	put_message(philo, EAT);
	pthread_mutex_lock(&philo->data->mutex_g);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->data->mutex_g);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->mutex_g);
	philo->meal_counters += 1;
	pthread_mutex_unlock(&philo->data->mutex_g);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	put_message(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	put_message(philo, THINK);
	return (0);
}

void	*routine(void	*arg)
{
	t_philo	*philo;
	int		isalive;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->mutex_g);
	isalive = philo->data->is_alive;
	pthread_mutex_unlock(&philo->data->mutex_g);
	while (isalive)
	{
		if (init_diner(philo))
			break ;
		pthread_mutex_lock(&philo->data->mutex_g);
		isalive = philo->data->is_alive;
		pthread_mutex_unlock(&philo->data->mutex_g);
	}
	return (NULL);
}
