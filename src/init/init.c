/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:27:49 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 10:38:57 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_null(t_data *data)
{
	data->map = NULL;
	data->player = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->settings = NULL;
}

t_data	*data_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	init_null(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1024, 1024, "Test");
}
