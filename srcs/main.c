#include "philosophers.h"
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
	pthread_mutex_unlock(philo->right_fork);
	/* ILS MANGENT */
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->data->mutex_g);
	philo->meal_counters++;
	pthread_mutex_unlock(&philo->data->mutex_g);
	put_message(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	put_message(philo, THINK);
	return (0);
}

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->data->nb_of_philo > 1 && philo->id == 2)
	// 	ft_usleep(1);
	while (philo->data->is_alive)
	{
		if (init_diner(philo))
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_error(NB_ARG_ERR, 1));
	if (!init_data(&data, ac, av))
		return (1);
	if (check_errors(av))
		return (ft_error(ONLY_NB_ERR, 1));
	if (!init_all(&data))
	{
		free_all(&data);
		return (1);
	}
	monitoring(&data);
	int i = 0;
	while (i < data.nb_of_philo)
	{
		pthread_mutex_destroy(&data.mutex[i]);
		pthread_join(data.th[i], NULL);
		i++;
	}
}
