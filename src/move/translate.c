/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:41:44 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/09 14:34:54 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	translate_forward(t_data *data, t_player *p)
{
	if (data->map->tiles[(int)(p->y)][(int)(p->x + p->dir_x * MOV_STEP)] \
			== tile_wall)
		p->x += p->dir_x * MOV_STEP;
	else
		p->x = (int)(p->x + p->dir_x * MOV_STEP) + \
				(p->dir_x > 0) * (-0.1) + (p->dir_x < 0) * (1.1);
	if (data->map->tiles[(int)(p->y + p->dir_y * MOV_STEP)][(int)(p->x)] \
			== tile_wall)
		p->y += p->dir_y * MOV_STEP;
	else
		p->y = (int)(p->y + p->dir_y * MOV_STEP) + \
				(p->dir_y > 0) * (-0.1) + (p->dir_y < 0) * (1.1);
}

static void	translate_backward(t_data *data, t_player *p)
{
	if (data->map->tiles[(int)(p->y)][(int)(p->x - p->dir_x * MOV_STEP)] \
			== tile_wall)
		p->x -= p->dir_x * MOV_STEP;
	else
		p->x = (int)(p->x - p->dir_x * MOV_STEP) + \
				(p->dir_x > 0) * (1.1) + (p->dir_x < 0) * (-0.1);
	if (data->map->tiles[(int)(p->y + p->dir_y * MOV_STEP)][(int)(p->x)] \
			== tile_wall)
		p->y -= p->dir_y * MOV_STEP;
	else
		p->y = (int)(p->y - p->dir_y * MOV_STEP) + \
				(p->dir_y > 0) * (1.1) + (p->dir_y < 0) * (-0.1);
}

/*static void	translate_right(t_data *data)
{
	
}

static void	translate_left(t_data *data)
{
	
}*/

void	translate(t_data *data)
{
	if (data->player->mov_forward && !(data->player->mov_backward))
		translate_forward(data, data->player);
	if (data->player->mov_backward && !(data->player->mov_forward))
		translate_backward(data, data->player);
	/*if (data->player->strafe_left && !(data->player->strafe_right))
		translate_left(data, data->player);
	if (data->player->strafe_right && !(data->player->strafe_left))
		translate_right(data, data->player);*/
}
