/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_wall2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:55:46 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/04 19:18:29 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../utils/hashtable.h"

static void	close_free_exit_1(char **str_arr, t_data *data, int fd)
{
	close(fd);
	free_strarray(str_arr);
	error_msg_exit(data, "Error parsing wall image properties");
}

static void	close_free_exit_2(t_data *data, char *line, char *helper, int fd)
{
	close(fd);
	free(line);
	free(helper);
	error_msg_exit(data, "Error parsing wall image properties");
}

void	wall_parse_properties(t_image *wall, char *line, t_data *data, int fd)
{
	char	*helper;
	char	**str_arr;
	int		i;
	int		e;

	helper = ft_strtrim(line, ",\"\n");
	str_arr = ft_split(helper, ' ');
	free(helper);
	if (str_arr_len(str_arr) != 4)
		close_free_exit_1(str_arr, data, fd);
	i = 0;
	while (str_arr[i])
	{
		if (!is_number(str_arr[i]))
			close_free_exit_1(str_arr, data, fd);
		i++;
	}
	e = 0;
	wall->width = ft_atoi_e(str_arr[0], &e);
	wall->height = ft_atoi_e(str_arr[1], &e);
	wall->n_keys = ft_atoi_e(str_arr[2], &e);
	wall->key_len = ft_atoi_e(str_arr[3], &e);
	if (e == 1)
		close_free_exit_1(str_arr, data, fd);
	free_strarray(str_arr);
}

void	wall_parse_keys(t_image *wall, char *line, t_data *data, int fd)
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
		close(fd);
		error_msg_exit(data, "Error when parsing image keys");
	}
	key = ft_calloc(wall->key_len + 1, 1);
	ft_strlcat(key, helper2, wall->key_len + 1);
	hashtable_add(wall->hashtable, 100, key, \
					ft_atoi_base_e(&(helper2[wall->key_len + 4]), 16, 0));
	free(key);
	free(helper2);
}

void	wall_parse_pixels(t_image *wall, char *line, int fd, int i)
{
	char	*helper1;
	char	*helper2;
	int		j;

	helper1 = ft_strtrim(line, ",\n");
	helper2 = ft_strtrim(helper1, "\"");
	free(helper1);
	if ((int)ft_strlen(helper2) != wall->width * wall->key_len)
		close_free_exit_2(wall->data, line, helper2, fd);
	j = 0;
	while (j < wall->width)
	{
		helper1 = get_first_n_chars(&(helper2[j * wall->key_len]), \
									wall->key_len);
		if (!helper1 || (i - 6 - wall->n_keys < 0))
			close_free_exit_2(wall->data, line, helper2, fd);
		wall->pixels[i - 6 - wall->n_keys][j] = \
								hashtable_get(wall->hashtable, 100, helper1);
		free(helper1);
		j++;
	}
	free(helper2);
}
