/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:36:36 by hfattah           #+#    #+#             */
/*   Updated: 2024/09/10 11:18:35 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_one_func(void *void_philosopher)
{
	t_philosopher	*philosopher;
	t_data			*data;

	philosopher = (t_philosopher *)void_philosopher;
	data = philosopher->data;
	pthread_mutex_lock(&data->forks[0]);
	philosopher_writer(philosopher, "has taken a fork");
	pthread_mutex_unlock(&data->forks[0]);
	philosopher_wait(data, data->time_to_die);
	philosopher_writer(philosopher, "died");
	return (NULL);
}

void	philosopher_one(t_data *data)
{
	data->start_time = get_time_milliseconds();
	if (pthread_create(&data->philosophers[0].thread_id, NULL,
			philosopher_one_func, &data->philosophers[0]) != 0)
	{
		printf("error : pthread_create");
		clear_data(data);
		return ;
	}
	pthread_join(data->philosophers[0].thread_id, NULL);
	clear_data(data);
}
