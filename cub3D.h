/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:05:28 by helensirenk       #+#    #+#             */
/*   Updated: 2024/09/30 18:44:04 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TILE_SIZE 64
# define FOV 60

/*COLORS*/
# define BLACK   0x000000
# define WHITE   0xFFFFFF
# define RED     0xFF0000
# define GREEN   0x00FF00
# define BLUE    0x0000FF
# define YELLOW  0xFFFF00
# define ORANGE  0xFFA500
# define PURPLE  0x800080
# define CYAN    0x00FFFF
# define MAGENTA 0xFF00FF

# define PSYCHEDELIC_PINK    0xFF1493
# define PSYCHEDELIC_LIME    0x32CD32
# define PSYCHEDELIC_CYAN    0x00FFFF
# define PSYCHEDELIC_YELLOW  0xFFFF00
# define PSYCHEDELIC_PURPLE  0x9400D3

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;

}	t_img;

typedef struct s_mapdata
{
	char	**map2d;
	int		map_h;
	int		map_w;

}	t_mapdata;

typedef struct s_pLayer
{
	int		player_x;
	int		player_y;
	double	angle;
	float	fov_radians;
}	t_player;

typedef struct s_ray
{
	double	hrz_x;
	double	hrz_y;
	double	vrt_x;
	double	vrt_y;
	double	ray_angle;
	int		flag;
	int		dist;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_mapdata	mapdata;
	int			color_floor;
	int			color_ceiling;
	t_img		img;
	t_player	*player;
	t_ray		*ray;
}	t_game;

//raycasting
int		hit_the_wall(float x, float y, t_game *game);

//utils
size_t	ft_strlen(const char *str);
int		unit_circle(float angle, char c);
float	normalz_angle(float angle);

// parsing
void init_struct_game(t_game *game, char * file_name);
void draw_ceiling_and_floor(t_game* game);

#endif