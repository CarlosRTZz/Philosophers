#include "philosophers.h"

void	free_all(t_data *data)
{
	if (data->mutex)
		free(data->mutex);
	if (data->philo)
		free(data->philo);
	if (data->th)
		free(data->th);
}
