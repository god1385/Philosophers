/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pos31d0n <pos31d0n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:44 by pos31d0n          #+#    #+#             */
/*   Updated: 2022/06/20 15:48:47 by pos31d0n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_addition	addition;
	pthread_t	*tid;
	int			j;

	addition.all_num = atoi(argv[1]);
	addition.die = atoi(argv[2]);
	addition.eat = atoi(argv[3]);
	addition.sleep = atoi(argv[4]);
	addition.start = ft_time();
	if (argc == 6)
		addition.need_to_eat = atoi(argv[5]);
	if (!init_mutex(&addition))
		return (0);
	philo = init_philos(&addition);
	j = 0;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * addition.all_num);
	if (!tid)
		return (0);
	if (addition.all_num == 1)
	{
		print_info(&philo[j], "died");
		return (1);
	}
	while (j < addition.all_num)
	{
		pthread_create(&tid[j], NULL, eating, &philo[j]);
		j++;
	}
	if (monitor(philo))
	{
		j = 0;
		while (philo[j].flag == 0)
		{
			pthread_join(tid[j], NULL);
			j++;
		}
		return (1);
	}
	return (0);
	pthread_exit(0);
}
