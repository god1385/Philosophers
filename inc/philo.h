/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pos31d0n <pos31d0n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:59:59 by pos31d0n          #+#    #+#             */
/*   Updated: 2022/06/20 15:29:02 by pos31d0n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define    MAX 100000

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_addition{
	pthread_mutex_t		message;
	pthread_mutex_t		*forks;
	int					die;
	int					sleep;
	int					eat;
	int					naelsya;
	int					all_num;
	int					need_to_eat;	
	unsigned long		start;
}				t_addition;

typedef struct s_philo{
	unsigned long		last_ate;
	t_addition			*addition;
	int					number;
	int					number_eat;
	int					flag;
}				t_philo;

unsigned long	ft_time(void);
t_philo			*check(t_philo *j);
t_philo			*init_philos(t_addition *addition);
void			*eating(void *number);
void			*potok(void *number);
void			ft_usleep(int time_to_wait);
void			print_info(t_philo *philo, char *msg);
int				init_mutex(t_addition *addition);
int				monitor(t_philo *philo);

#endif