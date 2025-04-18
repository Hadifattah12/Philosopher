/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:36:24 by hfattah           #+#    #+#             */
/*   Updated: 2024/09/10 11:19:11 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **argv)
{
	int	i;
	int	philosophers;
	int	philosopher_must_eat;
	int	arg;

	philosophers = ft_atoi(argv[1]);
	if (philosophers < 1 || philosophers > __INT_MAX__)
		return (0);
	if (argv[5] != NULL)
	{
		philosopher_must_eat = ft_atoi(argv[5]);
		if (philosopher_must_eat <= 0 || philosopher_must_eat > __INT_MAX__)
			return (0);
	}
	i = 2;
	while (i < 5)
	{
		arg = ft_atoi(argv[i]);
		if (arg <= 0 || arg > __INT_MAX__)
			return (0);
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (print_error("error : data->forks mutex_init"));
		i++;
	}
	if (pthread_mutex_init(&data->writer, NULL) != 0)
		return (print_error("error : data->writer mutex_init"));
	if (pthread_mutex_init(&data->is_eating, NULL) != 0)
		return (print_error("error : data->is_eating mutex_init"));
	if (pthread_mutex_init(&data->death_checker, NULL) != 0)
		return (print_error("error : data->death_checker mutex_init"));
	return (1);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].eating_count = 0;
		data->philosophers[i].last_eating_time = 0;
		data->philosophers[i].left_fork_id = i;
		data->philosophers[i].right_fork_id
			= (i + 1) % data->number_of_philosophers;
		data->philosophers[i].data = data;
		i++;
	}
}

int	init_data(t_data *data, char **argv)
{
	if (check_args(argv) == 0)
		return (print_error("error : invalid argument"));
	data->died_any_philosopher = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->philosopher_must_eat = -1;
	if (argv[5] != NULL)
		data->philosopher_must_eat = ft_atoi(argv[5]);
	data->philosophers
		= malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (data->philosophers == NULL)
		return (print_error("error : data->philosophers malloc"));
	data->forks
		= malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (data->forks == NULL)
		return (print_error("error : data->forks malloc"));
	if (init_mutexes(data) == 0)
		return (0);
	init_philosophers(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_error("error : argument count"));
	if (init_data(&data, argv) == 0)
		return (0);
	if (data.number_of_philosophers == 1)
	{
		philosopher_one(&data);
		return (0);
	}
	philosopher_many(&data);
	return (0);
}
