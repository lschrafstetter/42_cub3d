/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:45:15 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/02 09:59:45 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_image(t_image *image)
{
	if (image->hashtable)
		hashtable_delete(image->hashtable);
	if (image->pixels)
		free_intarray(image->pixels);
	free(image);
	image = NULL;
}

static void	free_walls(t_walls *walls)
{
	if (walls->n)
		free_image(walls->n);
	if (walls->e)
		free_image(walls->e);
	if (walls->s)
		free_image(walls->s);
	if (walls->w)
		free_image(walls->w);
	free(walls);
	walls = NULL;
}

static void	free_map(t_map *map)
{
	if (map->c_ceiling)
		free(map->c_ceiling);
	if (map->c_floor)
		free(map->c_floor);
	if (map->map)
		free_intarray(map->map);
	if (map->walls)
		free_walls(map->walls);
	free(map);
	map = NULL;
}

void	free_all(t_data *data)
{
	if (data->map)
		free_map(data->map);
	if (data->settings)
		free(data->settings);
	if (data->player)
		free(data->player);
	mlx_destroy(data);
	free(data);
	data = NULL;
}
