/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:03:54 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/09 14:35:18 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_scene(t_data *data)
{
	t_image	*image;

	image = image_init(data->mlx, SCREEN_HEIGHT, SCREEN_WIDTH);
	if (!image)
		error_msg_exit(data, "Error mallocing image!");
	//render_pov(data, image);
	render_minimap(data, image);
	mlx_put_image_to_window(data->mlx, data->win, image->image, 0, 0);
	mlx_destroy_image(data->mlx, image->image);
	free(image);
}
