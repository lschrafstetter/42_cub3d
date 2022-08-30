/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_properties.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:52:48 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 17:11:08 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	parse_str(t_data *data, char *str)
{
	if (data->map->map_found && (is_no_ea_so_we(str) || \
			!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2)))
		error_msg_exit(data, "Wrong input!");
	if (is_no_ea_so_we(str))
	{
		//parse_wall_image(data, str);
		return ;
	}
	if (!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2))
	{
		parse_floor_ceiling(data, str);
		return ;
	}
	if (!ft_strncmp(str, "\n", 2) && !(data->map->map_found))
		return ;
	if (is_map_line(str))
	{
		data->map->map_found = 1;
		data->map->heigth++;
		if ((int)(ft_strlen(str) - 1) > data->map->width)
			data->map->width = ft_strlen(str) - 1;
		return ;
	}
	error_msg_exit(data, "Wrong input!");
}

void	parse_map_properties(t_data *data, char *map_path)
{
	int		fd;
	char	*str;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		error_msg_exit(data, "Error opening map file!");
	str = get_next_line(fd);
	while (str)
	{
		parse_str(data, str);
		free(str);
		str = get_next_line(fd);
	}
	printf("Height: %i Width: %i\n", data->map->heigth, data->map->width);
	printf("Colors floor: r: %i, g: %i, b: %i\n", data->map->c_floor->r, data->map->c_floor->g, data->map->c_floor->b);
	printf("Colors ceiling: r: %i, g: %i, b: %i\n", data->map->c_ceiling->r, data->map->c_ceiling->g, data->map->c_ceiling->b);
}
