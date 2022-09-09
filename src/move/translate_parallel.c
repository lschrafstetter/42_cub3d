/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_parallel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:36:47 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/08 14:30:10 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_door_or_wall(int tile)
{
	return (tile == tile_wall || tile == tile_door);
}

void	translate_parallel_x_pos(t_data *data, float distance)
{
	if (is_door_or_wall(data->map->tiles[(int)(data->player->y)] \
		[(int)(data->player->x + (distance + 0.1))]))
		data->player->x = (int)(data->player->x + distance) + 0.9;
	else
		data->player->x = data->player->x + distance;
}

void	translate_parallel_x_neg(t_data *data, float distance)
{
	if (is_door_or_wall(data->map->tiles[(int)(data->player->y)] \
		[(int)(data->player->x - (distance + 0.1))]))
		data->player->x = (int)(data->player->x + distance) + 0.1;
	else
		data->player->x = data->player->x - distance;
}

void	translate_parallel_y_pos(t_data *data, float distance)
{
	if (is_door_or_wall(data->map->tiles \
		[(int)(data->player->y + (distance + 0.1))][(int)(data->player->x)]))
		data->player->y = (int)(data->player->y + distance) + 0.9;
	else
		data->player->y = data->player->y + distance;
}

void	translate_parallel_y_neg(t_data *data, float distance)
{
	if (is_door_or_wall(data->map->tiles \
		[(int)(data->player->y - (distance + 0.1))][(int)(data->player->x)]))
		data->player->y = (int)(data->player->y + distance) + 0.1;
	else
		data->player->y = data->player->y - distance;
}
