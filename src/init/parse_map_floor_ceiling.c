/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_floor_ceiling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:32:46 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/31 13:10:00 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**prepare_string_array(char *str)
{
	char	*helper;
	char	**str_arr;

	helper = ft_strtrim(str, "\n");
	str_arr = ft_split(helper, ',');
	free(helper);
	return (str_arr);
}

t_rgb_triple	*parse_rgb_triple(char *str)
{
	t_rgb_triple	*rgb_triple;
	__uint8_t		*rgb;
	char			**str_arr;
	int				i;

	rgb_triple = malloc(sizeof(t_rgb_triple));
	if (!rgb_triple)
		return (NULL);
	rgb = (__uint8_t *)rgb_triple;
	str_arr = prepare_string_array(&(str[2]));
	i = 0;
	while (str_arr[i++])
	{
		if (is_number(str_arr[i - 1]) && i < 4)
			rgb[i - 1] = ft_atoi(str_arr[i - 1]);
		else
		{
			free_strarray(str_arr);
			free(rgb_triple);
			return (NULL);
		}
	}
	free_strarray(str_arr);
	return (rgb_triple);
}

void	parse_floor_ceiling(t_data *data, char *str)
{
	t_rgb_triple	*rgb;

	rgb = parse_rgb_triple(str);
	if (!rgb)
		error_msg_exit(data, "Error parsing floor/ceiling color");
	if (!ft_strncmp(str, "F", 1))
	{
		if (data->map->c_floor)
		{
			free(rgb);
			error_msg_exit(data, "Two floors detected!");
		}
		data->map->c_floor = encode_rgb(rgb->r, rgb->g, rgb->b);
	}
	else if (!ft_strncmp(str, "C", 1))
	{
		if (data->map->c_ceiling)
		{
			free(rgb);
			error_msg_exit(data, "Two floors detected!");
		}
		data->map->c_ceiling = encode_rgb(rgb->r, rgb->g, rgb->b);
	}
	free(rgb);
}
