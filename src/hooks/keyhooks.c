/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:58:57 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 10:57:43 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_key(int keycode, t_data *data, bool pressed)
{
	if (keycode == KEY_W)
		data->player->mov_forward = pressed;
	if (keycode == KEY_S)
		data->player->mov_backward = pressed;
	if (keycode == KEY_A)
		data->player->strafe_left = pressed;
	if (keycode == KEY_D)
		data->player->strafe_right = pressed;
	if (keycode == KEY_ARROW_LEFT)
		data->player->rot_left = pressed;
	if (keycode == KEY_ARROW_RIGHT)
		data->player->rot_right = pressed;
}

int	hook_key_press(int keycode, t_data *data)
{
	//printf("Pressed key: %i!\n", keycode);
	if (keycode == KEY_ESCAPE)
		{}//cub_exit(data, 0);
	else
		handle_key(keycode, data, true);
	return (0);
}

int	hook_key_release(int keycode, t_data *data)
{
	//printf("Released key: %i!\n", keycode);
	handle_key(keycode, data, false);
	return (0);
}
