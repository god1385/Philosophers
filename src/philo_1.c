/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pos31d0n <pos31d0n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:29:59 by pos31d0n          #+#    #+#             */
/*   Updated: 2022/06/20 16:16:23 by pos31d0n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	ft_usleep(int time_to_wait)
{
	unsigned long	time;

	time = ft_time();
	while (ft_time() < time + (unsigned long)time_to_wait)
		usleep(100);
}

void	print_info(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->addition->message);
	if (philo->flag)
		printf("%lu %d %s\n",
			ft_time() - philo->addition->start, philo->number, msg);
	pthread_mutex_unlock(&philo->addition->message);
}

t_philo	*check(t_philo *j)
{
	j->number_eat++;
	if (j->addition->need_to_eat == j->number_eat)
		j->flag = 0;
	return (j);
}

void	*eating(void *number)
{
	t_philo	*j;

	j = (t_philo *)number;
	if (j->number % 2 == 1)
		usleep(50);
	while (j->flag != 0)
	{
		pthread_mutex_lock(&j->addition->forks[j->number - 1]);
		pthread_mutex_lock(&j->addition->forks[j->number % j->addition->all_num]);
		print_info(j, "has taken a fork");
		print_info(j, "has taken a fork");
		print_info(j, "is eating");
		ft_usleep(j->addition->eat);
		pthread_mutex_unlock(&j->addition->forks[j->number - 1]);
		pthread_mutex_unlock(&j->addition->forks[j->number % j->addition->all_num]);
		j->last_ate = ft_time();
		j = check(j);
		print_info(j, "is sleeping");
		ft_usleep(j->addition->sleep);
		print_info(j, "is thinking");
	}
	return (NULL);
}
