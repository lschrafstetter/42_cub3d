/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousehooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:07 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/08 14:04:33 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	hook_mouse(int x, int y, t_data *data)
{
	int	tertiant;

	(void) y;
	tertiant = SCREEN_WIDTH / 3;
	data->player->rot_left = (x < tertiant);
	data->player->rot_right = (x > SCREEN_WIDTH - tertiant);
	return (0);
}
