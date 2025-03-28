/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_many.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:36:32 by hfattah           #+#    #+#             */
/*   Updated: 2024/09/10 10:54:52 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_and_clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread_id, NULL);
		i++;
	}
	clear_data(data);
}

int	all_ate(t_data *data)
{
	int	i;

	i = 0;
	if (data->philosopher_must_eat <= 0)
		return (0);
	pthread_mutex_lock(&data->is_eating);
	while (i < data->number_of_philosophers)
	{
		if (data->philosophers[i].eating_count < data->philosopher_must_eat)
		{
			pthread_mutex_unlock(&data->is_eating);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->is_eating);
	return (1);
}

void	catch_death_or_eat(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (all_ate(data) == 1)
			break ;
		pthread_mutex_lock(&data->is_eating);
		if (data->philosophers[i].last_eating_time > 0
			&& get_time_milliseconds() - data->philosophers[i].last_eating_time
			> data->time_to_die)
		{
			philosopher_writer(&data->philosophers[i], "died");
			pthread_mutex_lock(&data->death_checker);
			data->died_any_philosopher = 1;
			pthread_mutex_unlock(&data->death_checker);
			pthread_mutex_unlock(&data->is_eating);
			break ;
		}
		pthread_mutex_unlock(&data->is_eating);
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
}

void	*philosopher_many_func(void *void_philosopher)
{
	t_philosopher	*philosopher;
	t_data			*data;

	philosopher = (t_philosopher *)void_philosopher;
	data = philosopher->data;
	if (philosopher->id % 2 == 1)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&data->death_checker);
		if (data->died_any_philosopher == 1)
		{
			pthread_mutex_unlock(&data->death_checker);
			break ;
		}
		pthread_mutex_unlock(&data->death_checker);
		if (data->philosopher_must_eat > 0
			&& philosopher->eating_count >= data->philosopher_must_eat)
			break ;
		philosopher_eat(data, philosopher);
		philosopher_sleep(data, philosopher);
		philosopher_think(philosopher);
	}
	return (NULL);
}

void	philosopher_many(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_milliseconds();
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread_id, NULL,
				philosopher_many_func, &data->philosophers[i]) != 0)
		{
			print_error("error : pthread_create");
			clear_data(data);
			return ;
		}
		i++;
	}
	catch_death_or_eat(data);
	join_and_clear(data);
}
