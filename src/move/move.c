/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:50:09 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 13:37:17 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void rotate(t_data *data)
{
	if (data->player->rot_left)
		data->player->dir += ROT_STEP;
	if (data->player->rot_right)
		data->player->dir -= ROT_STEP;
	if (data->player->dir >= 0)
		data->player->dir_int = (int)(data->player->dir) % 360;
	else
		data->player->dir_int = 360 + ((int)(data->player->dir) % 360);
}

void move(t_data *data)
{
	rotate(data);
	translate(data);
}
