/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:27:49 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/04 18:32:58 by lschrafs         ###   ########.fr       */
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

t_data	*data_init(char *map_path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	init_null(data);
	parse_map_file(data, map_path);
	check_map_init_player(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1024, 1024, "cub3d");
	return (data);
}
