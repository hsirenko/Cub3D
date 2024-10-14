/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:05:28 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/14 16:16:38 by helensirenk      ###   ########.fr       */
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
# define FOV 60
# define ROTATION_SPEED 0.05
# define PLAYER_SPEED 3

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

typedef enum action
{
	PRESS = 1,
	RELEASE = 0,
	REPEAT = 2,
}	t_action;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;

}	t_img;

typedef struct s_image
{
	void *img;
	int img_h;
	int img_w;
} t_image;

typedef struct s_mapdata
{
	char	**map2d;
	char 	**map_check;
	int 	p_x;
	int		p_y;
	int 	map_h;
	int		map_w;
	t_image north_wall;
	t_image south_wall;
	t_image east_wall;
	t_image west_wall;
}	t_mapdata;


typedef struct s_player
{
	double		player_x;
	double		player_y;
	char	start_orient;
	double	angle;
	float	fov_radians;
}	t_player;


typedef struct s_vec2f {
	float x;
	float y;
} t_vec2f;


t_vec2f vec2f(float x, float y);
t_vec2f rotate_vec(t_vec2f vec, float angle);
t_vec2f vec2f_add(t_vec2f a, t_vec2f b);

typedef struct s_ray
{
	t_vec2f origin;
	// angle between (0, -1) (North direction) and the ray
	double angle;
}	t_ray;

typedef enum e_direction {
	DIRECTION_NORTH,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_EAST,
} t_direction;

typedef struct s_hit {
	int hit;
	double distance;
	t_direction face;
	float angle;
	float local_x;
} t_hit;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_mapdata	mapdata;
	int			color_floor;
	int			color_ceiling;
	t_img		img;
	t_player	player;
}	t_game;

typedef enum e_key {
	KEY_ESC = 65307,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
}
t_key;

int inside_wall(t_mapdata* map, t_vec2f pos);

//raycasting
int		hit_the_wall(float x, float y, t_game *game);
void	ray_casting(t_game *game);
void render_wall(t_game *game, int ray_counter, t_hit hit);

//player movements
void key_press(int key, void *game_void);
void rotate(t_game *game, int i);
void	move(t_game *game, double move_x, double move_y);
void	hook_move_rotate(t_game *game, double move_x, double move_y);

//utils
size_t	ft_strlen(const char *str);
int		unit_circle(float angle, char c);
float	nor_angle(float angle);
void my_mlx_pixel_put(t_img* img, int x, int y, int color);
void ft_exit(t_game *game);

// parsing
void init_struct_game(t_game *game, char * file_name);
void draw_floor_ceiling(t_game *game, int ray_counter, int t_pix, int b_pix);
int has_holes(t_mapdata map, t_player player);

//exec
int	execution(t_game *game);
void	draw_map(void *pixel);

#endif