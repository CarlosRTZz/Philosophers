/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:22:24 by cortiz            #+#    #+#             */
/*   Updated: 2023/06/05 12:43:31 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_error(NB_ARG_ERR, 1));
	if (check_errors(av))
		return (ft_error(ONLY_NB_ERR, 1));
	if (!init_data(&data, ac, av))
		return (1);
	if (!init_all(&data))
	{
		free_all(&data);
		return (1);
	}
	monitoring(&data);
	free_all(&data);
}
