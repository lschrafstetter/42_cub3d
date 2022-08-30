/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:30 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 10:06:24 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_key(int keycode, t_data *data)
{
	printf("Test!\n");
}

int	render_next_frame(t_data *data)
{
	printf("Hey!\n");
	sleep(1);
}

int	main(int argc, char *argv)
{
	t_data	*data;

	//data = data_init();
	data = malloc(sizeof(t_data));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1024, 1024, "Test");
	mlx_key_hook(data->win, hook_key, data);
	//mlx_hook(data->win, 17, 0, hook_exit, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}
