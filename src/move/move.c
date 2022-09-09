/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:50:09 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/09 14:37:23 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	rotate(t_player *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	if (p->rot_left)
	{
		p->dir_x = p->dir_x * cos(ROT_STEP) - p->dir_y * sin(ROT_STEP);
		p->dir_y = old_dir_x * sin(ROT_STEP) + p->dir_y * cos(ROT_STEP);
		p->plane_x = p->plane_x * cos(ROT_STEP) - p->plane_y * sin(ROT_STEP);
		p->plane_y = old_plane_x * sin(ROT_STEP) + p->plane_y * cos(ROT_STEP);
	}
	if (p->rot_right)
	{
		p->dir_x = p->dir_x * cos(-ROT_STEP) - p->dir_y * sin(-ROT_STEP);
		p->dir_y = old_dir_x * sin(-ROT_STEP) + p->dir_y * cos(-ROT_STEP);
		p->plane_x = p->plane_x * cos(-ROT_STEP) - p->plane_y * sin(-ROT_STEP);
		p->plane_y = old_plane_x * sin(-ROT_STEP) + \
						p->plane_y * cos(-ROT_STEP);
	}
}

void	move(t_data *data)
{
	rotate(data->player);
	translate(data);
}
