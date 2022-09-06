/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:23 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 15:58:23 by lschrafs         ###   ########.fr       */
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
# include <sys/time.h>

# define FRAMERATE 30.0
# define DELAY 1000000 / FRAMERATE
# define MOV_STEP 1 / FRAMERATE
# define ROT_STEP 45 / FRAMERATE

# define SCREEN_HEIGHT 1024
# define SCREEN_WIDTH 1024

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

typedef struct s_image
{
	void	*image;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_rgb_triple
{
	__uint8_t	r;
	__uint8_t	g;
	__uint8_t	b;
}	t_rgb_triple;

typedef struct s_wall
{
	struct s_hashlist	***hashtable;
	struct s_data		*data;
	int					**pixels;
	int					width;
	int					height;
	int					n_keys;
	int					key_len;
}	t_wall;

typedef struct s_walls
{
	t_wall	*n;
	t_wall	*e;
	t_wall	*s;
	t_wall	*w;
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
	int		dir_int;
	bool	mov_forward;
	bool	mov_backward;
	bool	rot_left;
	bool	rot_right;
	bool	strafe_left;
	bool	strafe_right;
}	t_player;

typedef struct s_math
{
	double		*sin;
	double		*cos;
	double		*tan;
}	t_math;

typedef struct s_data
{
	t_map		*map;
	t_player	*player;
	t_math		*math;
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
void		wall_parse_properties(t_wall *wall, char *line, \
									t_data *data, int fd);
void		wall_parse_keys(t_wall *wall, char *line, t_data *data, int fd);
void		wall_parse_pixels(t_wall *wall, char *line, int fd, int i);

void		check_map_init_player(t_data *data);
t_player	*player_init(t_data *data, int i, int j);

//* KEY AND MOUSE EVENTS *//

int			hook_key_press(int keycode, t_data *data);
int			hook_key_release(int keycode, t_data *data);
int			hook_mouse(int x, int y, t_data *data);
int			hook_exit(t_data *data);

//* NAVIGATION *//

void		move(t_data *data);
void		translate(t_data *data);
void		translate_parallel_x_pos(t_data *data, float distance);
void		translate_parallel_x_neg(t_data *data, float distance);
void		translate_parallel_y_pos(t_data *data, float distance);
void		translate_parallel_y_neg(t_data *data, float distance);
void		translate_diagonal_q1(t_data *data);
void		translate_diagonal_q2(t_data *data);
void		translate_diagonal_q3(t_data *data);
void		translate_diagonal_q4(t_data *data);

//* RENDERING *//

void		render_scene(t_data *data);
void		render_minimap(t_data *data, t_image *image);

//* UTILS PARSING *//

int			is_no_ea_so_we(char *str);
int			is_map_line(char *str);
int			*encode_rgb(__uint8_t red, __uint8_t green, __uint8_t blue);

//* UTILS RENDERING *//

t_image		*image_init(void *mlx, int height, int width);
void		image_pix_put(t_image *image, int x, int y, int color);

//* UTILS EXIT *//

void		error_msg_exit(t_data *data, char *str);
void		error_exit(char *str);
void		cub_exit(t_data *data, int exit_code);
void		free_all(t_data *data);
void		mlx_destroy(t_data *data);

//* UTILS MATH *//

t_math		*math_init(void);
void		math_free(t_math *math);

//* UTILS GENERAL *//

int			is_hex(char *str);
int			is_number(char *str);
void		free_strarray(char **arr);
int			str_arr_len(char **str_arr);
void		free_intarray(int **int_arr);
int			**array_init(int height, int width);
char		*get_first_n_chars(char *str, int n_chars);
void		delay(bool start, unsigned long time);

#endif