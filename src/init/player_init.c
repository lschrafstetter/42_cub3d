/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:24:29 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 09:18:34 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_player	*player_init(t_data *data, int i, int j)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!(player))
		error_msg_exit(data, "Error mallocing player");
	player->x = j;
	player->y = i;
	player->dir = 0;
	player->dir = ((data->map->tiles[i][j] == tile_p_n) * 90 + \
							(data->map->tiles[i][j] == tile_p_e) * 180 + \
							(data->map->tiles[i][j] == tile_p_s) * 270);
	player->mov_forward = false;
	player->mov_backward = false;
	player->rot_left = false;
	player->rot_right = false;
	player->strafe_left = false;
	player->strafe_right = false;
	return (player);
}
