/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:23:07 by cortiz            #+#    #+#             */
/*   Updated: 2023/06/05 11:23:08 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_is_dead(t_data *data)
{
	int	i;
	int	last_meal;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_lock(&data->mutex_g);
		last_meal = data->philo[i].last_meal;
		pthread_mutex_unlock(&data->mutex_g);
		if ((current_time() - last_meal) >= data->time_to_die)
		{
			put_message(&data->philo[i], "died");
			pthread_mutex_lock(&data->mutex_g);
			data->is_alive = 0;
			pthread_mutex_unlock(&data->mutex_g);
			break ;
		}
		i++;
	}
	return ;
}

void	check_meals(t_data *data)
{
	int	i;
	int	meal_counter;
	int	nbofmeal;

	nbofmeal = 0;
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_lock(&data->mutex_g);
		meal_counter = data->philo[i].meal_counters;
		pthread_mutex_unlock(&data->mutex_g);
		if (meal_counter >= data->nb_of_meal)
			nbofmeal++;
		i++;
	}
	if (nbofmeal == data->nb_of_philo)
	{
		pthread_mutex_lock(&data->mutex_g);
		data->is_alive = 0;
		pthread_mutex_unlock(&data->mutex_g);
	}
}

void	monitoring(t_data *data)
{
	int	isalive;

	pthread_mutex_lock(&data->mutex_g);
	isalive = data->is_alive;
	pthread_mutex_unlock(&data->mutex_g);
	while (isalive)
	{
		check_is_dead(data);
		if (data->nb_of_meal)
			check_meals(data);
		pthread_mutex_lock(&data->mutex_g);
		isalive = data->is_alive;
		pthread_mutex_unlock(&data->mutex_g);
	}
}
