/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:23 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 09:28:48 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include <mlx.h>
# else
#  include "../mlx/mlx.h"
# endif
# include "../libft/libft.h"
# include "utils/hashtable.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# ifdef __linux__
// Linux
enum e_keys
{
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_RIGHT = 65363,
	KEY_ESCAPE = 65307
};
# else
// Mac
enum e_keys
{
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_ESCAPE = 53,
	KEY_ARROW_LEFT = 123,
	KEY_ARROW_RIGHT = 124,
};
# endif

typedef struct s_rgb_triple
{
	__uint8_t	r;
	__uint8_t	g;
	__uint8_t	b;
}	t_rgb_triple;

typedef struct s_image
{
	struct s_hashlist	***hashtable;
	struct s_data		*data;
	int					**pixels;
	int					width;
	int					height;
	int					n_keys;
	int					key_len;
}	t_image;

typedef struct s_walls
{
	t_image	*n;
	t_image	*e;
	t_image	*s;
	t_image	*w;
}	t_walls;

enum e_tile
{
	tile_empty = 0,
	tile_floor = 1,
	tile_wall = 2,
	tile_door = 3,
	tile_p_n = 4,
	tile_p_e = 5,
	tile_p_s = 6,
	tile_p_w = 7
};

typedef struct s_map
{
	int				**tiles;
	t_walls			*walls;
	int				*c_floor;
	int				*c_ceiling;
	int				map_found;
	int				height;
	int				width;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir;
	bool	mov_forward;
	bool	mov_backward;
	bool	rot_left;
	bool	rot_right;
	bool	strafe_left;
	bool	strafe_right;
}	t_player;

typedef struct s_settings
{
	int			screen_width;
	int			screen_height;
}	t_settings;

typedef struct s_data
{
	t_map		*map;
	t_player	*player;
	t_settings	*settings;
	void		*mlx;
	void		*win;
}	t_data;

//* INIT AND PARSING *//

t_data		*data_init(char *map_path);
void		parse_map_file(t_data *data, char *map_path);

void		parse_map_properties(t_data *data, char *map_path);
void		parse_floor_ceiling(t_data *data, char *str);
void		parse_map_tiles(t_data *data, char *map_path);

void		parse_wall_image(t_data *data, char *str);
void		wall_parse_properties(t_image *wall, char *line, \
									t_data *data, int fd);
void		wall_parse_keys(t_image *wall, char *line, t_data *data, int fd);
void		wall_parse_pixels(t_image *wall, char *line, int fd, int i);

void		check_map_init_player(t_data *data);
t_player	*player_init(t_data *data, int i, int j);

//* KEY AND MOUSE EVENTS *//

int			hook_key_press(int keycode, t_data *data);
int			hook_key_release(int keycode, t_data *data);
int			hook_mouse(int x, int y, t_data *data);
int			hook_exit(t_data *data);

//* UTILS PARSING *//

int			is_no_ea_so_we(char *str);
int			is_map_line(char *str);
int			*encode_rgb(__uint8_t red, __uint8_t green, __uint8_t blue);

//* UTILS EXIT *//

void		error_msg_exit(t_data *data, char *str);
void		error_exit(char *str);
void		cub_exit(t_data *data, int exit_code);
void		free_all(t_data *data);
void		mlx_destroy(t_data *data);

//* UTILS GENERAL *//

int			is_hex(char *str);
int			is_number(char *str);
void		free_strarray(char **arr);
int			str_arr_len(char **str_arr);
void		free_intarray(int **int_arr);
int			**array_init(int height, int width);
char		*get_first_n_chars(char *str, int n_chars);

#endif