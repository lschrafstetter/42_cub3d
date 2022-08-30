/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:30 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 11:31:37 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_exit(t_data *data)
{
	cub_exit(data, 0);
	return (0);
}

int	hook_key(int keycode, t_data *data)
{
	(void) keycode;
	(void) data;
	printf("Test!\n");
	return (0);
}

int	render_next_frame(t_data *data)
{
	(void) data;
	printf("Hey!\n");
	sleep(1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2 || ft_strrchr(argv[1], '.') == NULL || \
			ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5) != 0)
		error_exit("Usage: [./cub3d <map.cub>]");
	data = data_init();
	mlx_key_hook(data->win, hook_key, data);
	mlx_hook(data->win, 17, 0, hook_exit, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}
