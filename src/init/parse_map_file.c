/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:25:26 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/10 09:34:37 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_map	*map_init(t_data *data)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		error_msg_exit(data, "Error malloc'ing map struct!\n");
	map->walls = malloc(sizeof(t_walls));
	if (!(map->walls))
		error_msg_exit(data, "Error malloc'ing wall struct!\n");
	map->walls->n = NULL;
	map->walls->e = NULL;
	map->walls->s = NULL;
	map->walls->w = NULL;
	map->walls->door = NULL;
	map->tiles = NULL;
	map->c_ceiling = NULL;
	map->c_floor = NULL;
	map->map_found = 0;
	map->height = 0;
	map->width = 0;
	return (map);
}

void	parse_map_file(t_data *data, char *map_path)
{
	data->map = map_init(data);
	parse_map_properties(data, map_path);
	parse_map_tiles(data, map_path);
}
