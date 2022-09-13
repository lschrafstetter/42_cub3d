/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_floor_ceiling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:32:46 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/13 14:26:07 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_rgb_triple	*get_rgb_triple(char **str_arr)
{
	t_rgb_triple	*rgb_triple;
	int				overflow;
	int				r;
	int				g;
	int				b;

	rgb_triple = malloc(sizeof(t_rgb_triple));
	if (!rgb_triple)
		return (NULL);
	overflow = 0;
	r = ft_atoi_e(str_arr[0], &overflow);
	g = ft_atoi_e(str_arr[1], &overflow);
	b = ft_atoi_e(str_arr[2], &overflow);
	free_strarray(str_arr);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0 || overflow)
	{
		free(rgb_triple);
		return (NULL);
	}
	rgb_triple->r = r;
	rgb_triple->g = g;
	rgb_triple->b = b;
	return (rgb_triple);
}

static char	*build_new_str_without_spaces(char **arr)
{
	char	*helper;
	char	*ret;
	int		i;
	int		j;

	helper = malloc(str_len_without_spaces(arr));
	if (!helper)
		return (NULL);
	j = 0;
	arr++;
	while (*arr)
	{
		i = 0;
		while ((*arr)[i])
		{
			while ((*arr)[i] == ' ')
				i++;
			helper[j++] = (*arr)[i++];
		}
		arr++;
	}
	ret = ft_strtrim(helper, "\n");
	free(helper);
	return (ret);
}

static char	**prepare_string_array(char **arr)
{
	char	*without_spaces;
	char	**str_arr;

	without_spaces = build_new_str_without_spaces(arr);
	if (!without_spaces)
		return (NULL);
	printf("Without spaces: (%s)\n", without_spaces);
	str_arr = ft_split(without_spaces, ',');
	free(without_spaces);
	return (str_arr);
}

t_rgb_triple	*parse_rgb_triple(char **arr)
{
	t_rgb_triple	*rgb_triple;
	char			**str_arr;

	str_arr = prepare_string_array(arr);
	if (!str_arr || str_arr_len(str_arr) != 3 || !is_number(str_arr[0]) || \
		!is_number(str_arr[1]) || !is_number(str_arr[2]))
	{
		if (str_arr)
			free_strarray(str_arr);
		return (NULL);
	}
	rgb_triple = get_rgb_triple(str_arr);
	return (rgb_triple);
}

int	parse_floor_ceiling(t_data *data, char **arr)
{
	t_rgb_triple	*rgb;

	rgb = parse_rgb_triple(arr);
	if (!rgb)
		return (1);
	if ((!ft_strncmp(arr[0], "F", 1) && data->map->c_floor) || \
		(!ft_strncmp(arr[0], "C", 1) && data->map->c_ceiling))
	{
		free(rgb);
		return (1);
	}
	if (!ft_strncmp(arr[0], "F", 1))
		data->map->c_floor = encode_rgb(rgb->r, rgb->g, rgb->b);
	else
		data->map->c_ceiling = encode_rgb(rgb->r, rgb->g, rgb->b);
	free(rgb);
	return (0);
}
