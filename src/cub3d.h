/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:23 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 11:13:22 by lschrafs         ###   ########.fr       */
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

enum e_tile
{
	tile_floor = 0,
	tile_wall = 1,
	tile_door = 2
};

typedef struct s_map
{
	int	**map;
	int	heigth;
	int	width;
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
	t_player	*player;
	t_settings	*settings;
	void		*mlx;
	void		*win;
}	t_data;

//* INIT AND PARSING *//

t_data	*data_init(void);

//* UTILS *//

void	error_exit(char *str);
void	cub_exit(t_data *data, int exit_code);
void	free_all(t_data *data);
void	mlx_destroy(t_data *data);

#endif