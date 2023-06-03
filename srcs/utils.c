#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (str[i])
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_error(char *str, int i)
{
	printf("%s\n", str);
	return (i);
}

int	has_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_errors(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!has_only_digit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	current_time()
{
	int	time_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return (time_ms);
}
