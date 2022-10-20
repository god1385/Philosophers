/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:43 by pos31d0n          #+#    #+#             */
/*   Updated: 2022/10/20 19:05:42 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*potok(void *number)
{
	t_philo	*j;

	j = (t_philo *)number;
	eating(j);
	return (NULL);
}

t_philo	*init_philos(t_addition *addition)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * addition->all_num);
	if (!philos)
		return (0);
	i = 0;
	while (i < addition->all_num)
	{
		philos[i].number = i + 1;
		philos[i].addition = addition;
		philos[i].last_ate = 0;
		philos[i].flag = 1;
		philos[i].number_eat = 0;
		i++;
	}
	return (philos);
}

int	init_mutex(t_addition *addition)
{
	int	i;

	addition->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * addition->all_num);
	if (!addition->forks)
		return (0);
	i = 0;
	while (i < addition->all_num)
	{
		if (pthread_mutex_init(&addition->forks[i], NULL) != 0)
		{
			free(addition->forks);
			return (0);
		}
		if (pthread_mutex_init(&addition->message, NULL) != 0)
		{
			free(addition->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	monitor(t_philo *philo)
{
	int	j;

	while (1)
	{
		j = 0;
		while (j < philo->addition->all_num)
		{
			if (philo[j].last_ate && ft_time()
				- philo[j].last_ate > (unsigned long)philo[j].addition->die)
			{
				print_info(&philo[j], "died");
				philo[j].flag = 0;
				return (1);
			}
			j++;
		}
	}
	return (1);
}
