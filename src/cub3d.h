/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:23 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 16:57:18 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include <mlx.h>
# else
#  include "../ext/mlx.h"
# endif
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# ifdef __linux__
// Linux
enum e_keys
{
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_W = 119,
	KEY_ARROW_UP = 65362,
	KEY_ARROW_DOWN = 65364,
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
	KEY_ESCAPE = 53
};
# endif

typedef struct s_rgb_triple
{
	__uint8_t	r;
	__uint8_t	g;
	__uint8_t	b;
}	t_rgb_triple;

typedef struct s_images
{
	t_rgb_triple	**wall_n;
	t_rgb_triple	**wall_e;
	t_rgb_triple	**wall_s;
	t_rgb_triple	**wall_w;
}	t_images;

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
	int				**map;
	t_rgb_triple	*c_floor;
	t_rgb_triple	*c_ceiling;
	int				map_found;
	int				heigth;
	int				width;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	int		dir;
}	t_player;

typedef struct s_settings
{
	int			screen_width;
	int			screen_height;
}	t_settings;

typedef struct s_data
{
	t_map		*map;
	t_images	*images;
	t_player	*player;
	t_settings	*settings;
	void		*mlx;
	void		*win;
}	t_data;

//* INIT AND PARSING *//

t_data	*data_init(char *map_path);
void	parse_map_file(t_data *data, char *map_path);
void	parse_map_properties(t_data *data, char *map_path);
void	parse_floor_ceiling(t_data *data, char *str);
void	parse_map_tiles(t_data *data, char *map_path);

//* KEY AND MOUSE EVENTS *//

int		hook_key_press(int keycode, t_data *data);
int		hook_key_release(int keycode, t_data *data);
int		hook_mouse(int x, int y, t_data *data);
int		hook_exit(t_data *data);

//* UTILS PARSING *//

int		is_no_ea_so_we(char *str);
int		is_map_line(char *str);

//* UTILS EXIT *//

void	error_msg_exit(t_data *data, char *str);
void	error_exit(char *str);
void	cub_exit(t_data *data, int exit_code);
void	free_all(t_data *data);
void	mlx_destroy(t_data *data);

//* UTILS GENERAL *//

void	free_strarray(char **arr);

#endif