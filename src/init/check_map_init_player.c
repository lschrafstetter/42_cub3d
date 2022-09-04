/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_init_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:33:28 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/04 18:56:45 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_tile_floor(t_data *data, int i, int j)
{
	if (i == 0 || j == 0 || \
		i == data->map->height - 1 || j == data->map->width - 1)
		error_msg_exit(data, "Floor on the map edge not allowed");
	if (data->map->tiles[i - 1][j] == tile_empty ||
		data->map->tiles[i + 1][j] == tile_empty ||
		data->map->tiles[i][j - 1] == tile_empty ||
		data->map->tiles[i][j + 1] == tile_empty)
		error_msg_exit(data, "Map not closed");
}

static void	check_tile_door(t_data *data, int i, int j)
{
	if (i == 0 || j == 0 || \
			i == data->map->height - 1 || j == data->map->width - 1)
		error_msg_exit(data, "Door on the map edge not allowed");
	if (data->map->tiles[i - 1][j] == tile_empty ||
		data->map->tiles[i + 1][j] == tile_empty ||
		data->map->tiles[i][j - 1] == tile_empty ||
		data->map->tiles[i][j + 1] == tile_empty)
		error_msg_exit(data, "Door into nothing. Not good.");
	if (data->map->tiles[i - 1][j] == tile_door ||
		data->map->tiles[i + 1][j] == tile_door ||
		data->map->tiles[i][j - 1] == tile_door ||
		data->map->tiles[i][j + 1] == tile_door)
		error_msg_exit(data, "Double doors are too fancy for this project");
}

static void	check_tile_player(t_data *data, int i, int j)
{
	if (i == 0 || j == 0 || \
			i == data->map->height - 1 || j == data->map->width - 1)
		error_msg_exit(data, "Player on the map edge not allowed");
	if (data->map->tiles[i - 1][j] == tile_empty ||
		data->map->tiles[i + 1][j] == tile_empty ||
		data->map->tiles[i][j - 1] == tile_empty ||
		data->map->tiles[i][j + 1] == tile_empty)
		error_msg_exit(data, "Player next to void. Don't do that.");
	if (data->player)
		error_msg_exit(data, "Multiple players detected");
	data->player = malloc(sizeof(t_player));
	if (!(data->player))
		error_msg_exit(data, "Error mallocing player");
	data->player->x = j;
	data->player->y = i;
	data->player->dir = ((data->map->tiles[i][j] == tile_p_n) * 90 + \
							(data->map->tiles[i][j] == tile_p_e) * 180 + \
							(data->map->tiles[i][j] == tile_p_s) * 270);
}

static void	check_tile(t_data *data, int i, int j)
{
	if (data->map->tiles[i][j] == tile_floor)
		check_tile_floor(data, i, j);
	else if (data->map->tiles[i][j] == tile_door)
		check_tile_door(data, i, j);
	else if (data->map->tiles[i][j] == tile_p_n || \
				data->map->tiles[i][j] == tile_p_e || \
				data->map->tiles[i][j] == tile_p_s || \
				data->map->tiles[i][j] == tile_p_w)
		check_tile_player(data, i, j);
}

void	check_map_init_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			j++;
			check_tile(data, i, j);
		}
		i++;
	}
	if (!(data->player))
		error_msg_exit(data, "No player");
}
