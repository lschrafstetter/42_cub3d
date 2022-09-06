/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:57:42 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 16:59:30 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	color_select(t_data *data, int i, int j)
{
	if (i < 0 || j < 0 || \
			i > data->map->height - 1 || j > data->map->width - 1)
		return (0xFFFFFF);
	else if (data->map->tiles[i][j] == tile_wall)
		return (0x0);
	else if (data->map->tiles[i][j] == tile_door)
		return (0x00FF00);
	else
		return (0xd3d3d3);
}

static void	draw_tile(t_data *data, t_image *image, int *indexes)
{
	int	color;
	int	i;
	int	j;
	int	target_i;
	int	target_j;

	color = color_select(data, indexes[0], indexes[1]);
	target_i = indexes[2] + 9;
	target_j = indexes[3] + 9;
	i = indexes[2];
	while (i < target_i)
	{
		j = indexes[3];
		while (j < target_j)
		{
			image_pix_put(image, j, i, color);
			j++;
		}
		i++;
	}
}

static void	draw_map(t_data *data, t_image *image, int *indexes)
{
	indexes[0] = (int)(data->player->y) - 9;
	indexes[1] = (int)(data->player->x) - 9;
	indexes[2] = 0;
	indexes[3] = 0;
	while (indexes[0] < (int)(data->player->y) + 9)
	{
		indexes[1] = (int)(data->player->x) - 9;
		indexes[3] = 0;
		while (indexes[1] < (int)(data->player->x) + 9)
		{
			draw_tile(data, image, indexes);
			indexes[1]++;
			indexes[3] += 10;
		}
		indexes[0]++;
		indexes[2] += 10;
	}
}

static void	draw_player(t_data *data, t_image *image)
{
	int	i;
	int	j;

	i = 87;
	while (i < 93)
	{
		j = 87;
		while (j < 93)
		{
			image_pix_put(image, i, j, 0xFF0000);
			j++;
		}
		i++;
	}
	(void) data;
}

void	render_minimap(t_data *data, t_image *image)
{
	int	*indexes;

	indexes = malloc(sizeof(int) * 4);
	if (!indexes)
	{
		free(image);///////////
		error_msg_exit(data, "Error mallocing int array");
	}
	draw_map(data, image, indexes);
	draw_player(data, image);
	free(indexes);
}
