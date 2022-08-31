/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_wall1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:21:14 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/31 14:59:34 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../utils/hashtable.h"

static void	close_free_exit(char *line, t_data *data, int fd)
{
	close(fd);
	free(line);
	error_msg_exit(data, "Error parsing wall image properties");
}

static void	parse_file(t_data *data, t_image *wall, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 1;
	while (line)
	{
		if (i == 4)
		{
			wall_parse_properties(wall, line, data, fd);
			wall->hashtable = hashtable_init(100);
			wall->pixels = array_init(wall->height, wall->width);
			if (!wall->pixels)
				close_free_exit(line, data, fd);
		}
		else if (i > 4 && i <= wall->n_keys + 4)
			wall_parse_keys(wall, line, data, fd);
		else if (i > wall->n_keys + 5 && i <= wall->n_keys + 5 + wall->height)
			wall_parse_pixels(wall, line, fd, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

static t_image	*parse_wall(t_data *data, char *str)
{
	t_image	*wall;
	char	*filename;
	int		fd;

	filename = ft_strtrim(&(str[3]), "\n");
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd < 0)
		error_msg_exit(data, "Error opening wall file!");
	wall = ft_calloc(sizeof(t_image), 1);
	if (!wall)
	{
		close(fd);
		error_msg_exit(data, "Error mallocing wall struct!");
	}
	wall->data = data;
	parse_file(data, wall, fd);
	return (wall);
}

void	parse_wall_image(t_data *data, char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
	{
		if (data->map->walls->n)
			error_msg_exit(data, "'NO' wall already exists!");
		data->map->walls->n = parse_wall(data, str);
		printf("n height: %i, width: %i, n_keys: %i, key_len: %i\n", data->map->walls->n->height, data->map->walls->n->width, data->map->walls->n->n_keys, data->map->walls->n->key_len);
	}
	else if (!ft_strncmp(str, "EA ", 3))
	{
		if (data->map->walls->e)
			error_msg_exit(data, "'EA' wall already exists!");
		data->map->walls->e = parse_wall(data, str);
		printf("e height: %i, width: %i, n_keys: %i, key_len: %i\n", data->map->walls->e->height, data->map->walls->e->width, data->map->walls->e->n_keys, data->map->walls->e->key_len);
	}
	else if (!ft_strncmp(str, "SO ", 3))
	{
		if (data->map->walls->s)
			error_msg_exit(data, "'SO' wall already exists!");
		data->map->walls->s = parse_wall(data, str);
		printf("s height: %i, width: %i, n_keys: %i, key_len: %i\n", data->map->walls->s->height, data->map->walls->s->width, data->map->walls->s->n_keys, data->map->walls->s->key_len);
	}
	else
	{
		if (data->map->walls->w)
			error_msg_exit(data, "'WE' wall already exists!");
		data->map->walls->w = parse_wall(data, str);
		printf("w height: %i, width: %i, n_keys: %i, key_len: %i\n", data->map->walls->w->height, data->map->walls->w->width, data->map->walls->w->n_keys, data->map->walls->w->key_len);
	}
}
