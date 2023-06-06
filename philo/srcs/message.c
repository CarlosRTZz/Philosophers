/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:22:41 by cortiz            #+#    #+#             */
/*   Updated: 2023/06/05 11:22:41 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	put_message(t_philo *philo, char *msg)
{
	int	time;
	int	is_alive;

	time = current_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->mutex_m);
	pthread_mutex_lock(&philo->data->mutex_g);
	is_alive = philo->data->is_alive;
	pthread_mutex_unlock(&philo->data->mutex_g);
	if (is_alive)
		printf("%d %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_m);
}
