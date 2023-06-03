#include "philosophers.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->is_alive = 1;
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->nb_of_philo < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (ft_error(VALID_NB_ERR, 0));
	if (ac == 6)
	{
		data->nb_of_meal = ft_atoi(av[5]);
		if (data->nb_of_meal < 1)
			return (ft_error(VALID_NB_ERR, 0));
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->mutex)
		return (ft_error("Malloc Error", 0));
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (ft_error("Error while creating mutex", 0));
		i++;
	}
	if (pthread_mutex_init(&data->mutex_g, NULL))
		return (ft_error("Error while creating mutex", 0));
	if (pthread_mutex_init(&data->mutex_m, NULL))
		return (ft_error("Error while creating mutex", 0));
	return (1);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		return (ft_error("Malloc Error", 0));
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = current_time();
		data->philo[i].left_fork = &data->mutex[i];
		if (i == data->nb_of_philo - 1)
			data->philo[i].right_fork = &data->mutex[0];
		else
			data->philo[i].right_fork = &data->mutex[i + 1];
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	data->th = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->th)
		return (ft_error("Malloc error", 0));
	data->start = current_time();
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->th[i], NULL, &routine, &data->philo[i]) != 0)
			return (ft_error("Error creating thread", 0));
		// printf("th %d created\n", i);
		i++;
	}
	return (1);
}

int	init_all(t_data *data)
{
	if (!init_mutex(data))
		return (0);
	if (!init_philo(data))
		return (0);
	if (!init_thread(data))
		return (0);
	return (1);
}
