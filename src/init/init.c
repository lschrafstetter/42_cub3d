/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:27:49 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/31 15:52:47 by lschrafs         ###   ########.fr       */
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

static void	print_wall(t_image *wall, t_data *data)
{
	int	i;
	int	j;

	(void) data;
	i = 0;
	while (i < wall->height)
	{
		j = 0;
		while (j < wall->width)
		{
			//printf("(%i|%i)", i, j);
			mlx_pixel_put(data->mlx, data->win, j, i, wall->pixels[i][j]);
			j++;
		}
		//printf("\n");
		i++;
	}
}

t_data	*data_init(char *map_path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	init_null(data);
	parse_map_file(data, map_path);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1024, 1024, "cub3d");
	print_wall(data->map->walls->w, data);
	return (data);
}
