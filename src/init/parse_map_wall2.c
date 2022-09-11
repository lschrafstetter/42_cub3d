/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_wall2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:55:46 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/11 10:43:46 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../utils/hashtable.h"

int	wall_parse_properties(t_wall *wall, char *line)
{
	char	*helper;
	char	**str_arr;
	int		i;
	int		e;

	helper = ft_strtrim(line, ",\"\n");
	str_arr = ft_split(helper, ' ');
	free(helper);
	if (str_arr_len(str_arr) != 4)
	{
		free_strarray(str_arr);
		printf("Str array!\n");//
		return (1);
	}
	i = 0;
	while (str_arr[i])
	{
		if (!is_number(str_arr[i]))
		{
			free_strarray(str_arr);
			printf("Not a number!\n");//
			return (1);
		}
		i++;
	}
	e = 0;
	wall->width = ft_atoi_e(str_arr[0], &e);
	wall->height = ft_atoi_e(str_arr[1], &e);
	wall->n_keys = ft_atoi_e(str_arr[2], &e);
	wall->key_len = ft_atoi_e(str_arr[3], &e);
	free_strarray(str_arr);
	if (e == 1)
	{
		printf("Overflow!\n");//
		return (1);
	}
	return (0);
}

int	wall_parse_keys(t_wall *wall, char *line)
{
	char	*helper1;
	char	*helper2;
	char	*key;

	helper1 = ft_strtrim(line, ",\n");
	helper2 = ft_strtrim(helper1, "\"");
	free(helper1);
	if ((int)ft_strlen(helper2) != wall->key_len + 10 || \
		ft_strncmp(&(helper2[wall->key_len]), " c #", 4) || \
		!is_hex(&(helper2[wall->key_len + 4])))
	{
		free(helper2);
		return (1);
	}
	key = ft_calloc(wall->key_len + 1, 1);
	ft_strlcat(key, helper2, wall->key_len + 1);
	hashtable_add(wall->hashtable, 100, key, \
					ft_atoi_base_e(&(helper2[wall->key_len + 4]), 16, 0));
	free(key);
	free(helper2);
	return (0);
}

int	wall_parse_pixels(t_wall *wall, char *line, int i)
{
	char	*helper1;
	char	*helper2;
	int		j;

	helper1 = ft_strtrim(line, ",\n");
	helper2 = ft_strtrim(helper1, "\"");
	free(helper1);
	if ((int)ft_strlen(helper2) != wall->width * wall->key_len)
	{
		free(helper2);
		return (1);
	}
	j = 0;
	while (j < wall->width)
	{
		helper1 = get_first_n_chars(&(helper2[j * wall->key_len]), \
									wall->key_len);
		if (!helper1 || (i - 6 - wall->n_keys < 0))
		{
			free(helper2);
			return (1);
		}
		wall->pixels[i - 6 - wall->n_keys][j] = \
								hashtable_get(wall->hashtable, 100, helper1);
		free(helper1);
		j++;
	}
	free(helper2);
	return (0);
}
