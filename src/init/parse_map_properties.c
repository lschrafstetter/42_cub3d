/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_properties.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:52:48 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 09:23:44 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	close_free_exit(t_data *data, char *str, int fd)
{
	close(fd);
	free(str);
	error_msg_exit(data, "Wrong input!");
}

static void	parse_str(t_data *data, char *str, int fd)
{
	if (data->map->map_found && (is_no_ea_so_we(str) || \
			!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2)))
		close_free_exit(data, str, fd);
	if (is_no_ea_so_we(str))
	{
		parse_wall_image(data, str);
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
		data->map->height++;
		if ((int)(ft_strlen(str) - 1) > data->map->width)
			data->map->width = ft_strlen(str) - 1;
		return ;
	}
	close_free_exit(data, str, fd);
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
		parse_str(data, str, fd);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
}
