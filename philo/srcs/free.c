/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:21:27 by cortiz            #+#    #+#             */
/*   Updated: 2023/06/05 12:10:44 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->th[i], NULL);
		i++;
	}
}

void	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->mutex_g);
	pthread_mutex_destroy(&data->mutex_m);
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i++;
	}
}

void	free_all(t_data *data)
{
	if (data->th)
		join_thread(data);
	if (data->mutex)
		destroy_mutex(data);
	if (data->mutex)
		free(data->mutex);
	if (data->philo)
		free(data->philo);
	if (data->th)
		free(data->th);
}
