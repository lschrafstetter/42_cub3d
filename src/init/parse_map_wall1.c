/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_wall1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:21:14 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/11 10:46:15 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../utils/hashtable.h"

static t_wall	*wall_init(t_data *data)
{
	t_wall	*wall;

	wall = ft_calloc(sizeof(t_wall), 1);
	if (!wall)
		return (NULL);
	wall->hashtable = NULL;
	wall->pixels = NULL;
	wall->data = data;
	wall->width = 0;
	wall->height = 0;
	return (wall);
}

static t_wall	*parse_file(t_data *data, int fd)
{
	t_wall	*wall;
	char	*line;
	int		i;

	wall = wall_init(data);
	if (!wall)
		return (NULL);
	line = get_next_line(fd);
	i = 1;
	while (line)
	{
		if (i == 4)
		{
			if (wall_parse_properties(wall, line))
			{
				free(line);
				printf("Wall properties\n");//
				return (NULL);
			}
			wall->hashtable = hashtable_init(100);
			if (!(wall->hashtable))
			{
				free(line);
				printf("Hashtable\n");//
				return (NULL);
			}
			wall->pixels = array_init(wall->height, wall->width);
			if (!wall->pixels)
			{
				free(line);
				printf("Pixel Array\n");//
				return (NULL);
			}
		}
		else if (i > 4 && i <= wall->n_keys + 4)
		{
			if (wall_parse_keys(wall, line))
			{
				free(line);
				printf("Parse Keys\n");//
				return (NULL);
			}
		}
		else if (i > wall->n_keys + 5 && i <= wall->n_keys + 5 + wall->height)
		{
			if (wall_parse_pixels(wall, line, i))
			{
				free(line);
				printf("Wall Parse Pixels\n");//
				return (NULL);
			}
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (wall);
}

static t_wall	*parse_wall(t_data *data, char *str)
{
	t_wall	*wall;
	char	*filename;
	int		fd_wall;

	filename = ft_strtrim(&(str[3]), "\n");
	if (ft_strncmp(ft_strrchr(filename, '.'), ".xpm", 5))////////
	{
		free(filename);
		return (NULL);
	}
	fd_wall = open(filename, O_RDONLY);
	free(filename);
	if (fd_wall < 0)
		return (NULL);
	wall = parse_file(data, fd_wall);
	close(fd_wall);
	return (wall);
}

int	parse_wall_image(t_data *data, char *str)
{
	t_wall	*wall_to_parse;

	if ((!ft_strncmp(str, "DO ", 3) && data->map->walls->door) || \
		(!ft_strncmp(str, "NO ", 3) && data->map->walls->n) || \
		(!ft_strncmp(str, "EA ", 3) && data->map->walls->e) || \
		(!ft_strncmp(str, "SO ", 3) && data->map->walls->s) || \
		(!ft_strncmp(str, "WE ", 3) && data->map->walls->w))
		return (1);
	if (!ft_strncmp(str, "DO ", 3))
		wall_to_parse = data->map->walls->door;
	else if (!ft_strncmp(str, "NO ", 3))
		wall_to_parse = data->map->walls->n;
	else if (!ft_strncmp(str, "EA ", 3))
		wall_to_parse = data->map->walls->e;
	else if (!ft_strncmp(str, "SO ", 3))
		wall_to_parse = data->map->walls->s;
	else
		wall_to_parse = data->map->walls->w;
	printf("%s\n", str);///
	wall_to_parse = parse_wall(data, str);
	if (!wall_to_parse)
		return (1);
	return (0);
}
