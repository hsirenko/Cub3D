/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:05:28 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/13 18:36:02 by kseniakarem      ###   ########.fr       */
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

// typedef enum s_key
// {
// 	KEY_W	= 87,
// 	KEY_LEFT = 263,
// 	KEY_RIGHT = 262,

// }	t_key;

typedef enum key
{
	MLX_KEY_SPACE			= 32,
	MLX_KEY_APOSTROPHE		= 39,
	MLX_KEY_COMMA			= 44,
	MLX_KEY_MINUS			= 45,
	MLX_KEY_PERIOD			= 46,
	MLX_KEY_SLASH			= 47,
	MLX_KEY_0				= 48,
	MLX_KEY_1				= 49,
	MLX_KEY_2				= 50,
	MLX_KEY_3				= 51,
	MLX_KEY_4				= 52,
	MLX_KEY_5				= 53,
	MLX_KEY_6				= 54,
	MLX_KEY_7				= 55,
	MLX_KEY_8				= 56,
	MLX_KEY_9				= 57,
	MLX_KEY_SEMICOLON		= 59,
	MLX_KEY_EQUAL			= 61,
	MLX_KEY_A				= 65,
	MLX_KEY_B				= 66,
	MLX_KEY_C				= 67,
	MLX_KEY_D				= 68,
	MLX_KEY_E				= 69,
	MLX_KEY_F				= 70,
	MLX_KEY_G				= 71,
	MLX_KEY_H				= 72,
	MLX_KEY_I				= 73,
	MLX_KEY_J				= 74,
	MLX_KEY_K				= 75,
	MLX_KEY_L				= 76,
	MLX_KEY_M				= 77,
	MLX_KEY_N				= 78,
	MLX_KEY_O				= 79,
	MLX_KEY_P				= 80,
	MLX_KEY_Q				= 81,
	MLX_KEY_R				= 82,
	MLX_KEY_S				= 83,
	MLX_KEY_T				= 84,
	MLX_KEY_U				= 85,
	MLX_KEY_V				= 86,
	MLX_KEY_W				= 87,
	MLX_KEY_X				= 88,
	MLX_KEY_Y				= 89,
	MLX_KEY_Z				= 90,
	MLX_KEY_LEFT_BRACKET	= 91,
	MLX_KEY_BACKSLASH		= 92,
	MLX_KEY_RIGHT_BRACKET	= 93,
	MLX_KEY_GRAVE_ACCENT	= 96,
	MLX_KEY_ESCAPE			= 256,
	MLX_KEY_ENTER			= 257,
	MLX_KEY_TAB				= 258,
	MLX_KEY_BACKSPACE		= 259,
	MLX_KEY_INSERT			= 260,
	MLX_KEY_DELETE			= 261,
	MLX_KEY_RIGHT			= 262,
	MLX_KEY_LEFT			= 263,
	MLX_KEY_DOWN			= 264,
	MLX_KEY_UP				= 265,
	MLX_KEY_PAGE_UP			= 266,
	MLX_KEY_PAGE_DOWN		= 267,
	MLX_KEY_HOME			= 268,
	MLX_KEY_END				= 269,
	MLX_KEY_CAPS_LOCK		= 280,
	MLX_KEY_SCROLL_LOCK		= 281,
	MLX_KEY_NUM_LOCK		= 282,
	MLX_KEY_PRINT_SCREEN	= 283,
	MLX_KEY_PAUSE			= 284,
	MLX_KEY_F1				= 290,
	MLX_KEY_F2				= 291,
	MLX_KEY_F3				= 292,
	MLX_KEY_F4				= 293,
	MLX_KEY_F5				= 294,
	MLX_KEY_F6				= 295,
	MLX_KEY_F7				= 296,
	MLX_KEY_F8				= 297,
	MLX_KEY_F9				= 298,
	MLX_KEY_F10				= 299,
	MLX_KEY_F11				= 300,
	MLX_KEY_F12				= 301,
	MLX_KEY_F13				= 302,
	MLX_KEY_F14				= 303,
	MLX_KEY_F15				= 304,
	MLX_KEY_F16				= 305,
	MLX_KEY_F17				= 306,
	MLX_KEY_F18				= 307,
	MLX_KEY_F19				= 308,
	MLX_KEY_F20				= 309,
	MLX_KEY_F21				= 310,
	MLX_KEY_F22				= 311,
	MLX_KEY_F23				= 312,
	MLX_KEY_F24				= 313,
	MLX_KEY_F25				= 314,
	MLX_KEY_KP_0			= 320,
	MLX_KEY_KP_1			= 321,
	MLX_KEY_KP_2			= 322,
	MLX_KEY_KP_3			= 323,
	MLX_KEY_KP_4			= 324,
	MLX_KEY_KP_5			= 325,
	MLX_KEY_KP_6			= 326,
	MLX_KEY_KP_7			= 327,
	MLX_KEY_KP_8			= 328,
	MLX_KEY_KP_9			= 329,
	MLX_KEY_KP_DECIMAL		= 330,
	MLX_KEY_KP_DIVIDE		= 331,
	MLX_KEY_KP_MULTIPLY		= 332,
	MLX_KEY_KP_SUBTRACT		= 333,
	MLX_KEY_KP_ADD			= 334,
	MLX_KEY_KP_ENTER		= 335,
	MLX_KEY_KP_EQUAL		= 336,
	MLX_KEY_LEFT_SHIFT		= 340,
	MLX_KEY_LEFT_CONTROL	= 341,
	MLX_KEY_LEFT_ALT		= 342,
	MLX_KEY_LEFT_SUPER		= 343,
	MLX_KEY_RIGHT_SHIFT		= 344,
	MLX_KEY_RIGHT_CONTROL	= 345,
	MLX_KEY_RIGHT_ALT		= 346,
	MLX_KEY_RIGHT_SUPER		= 347,
	MLX_KEY_MENU			= 348,
}	t_key;

typedef struct s_keydata
{
	t_key		key;
	t_action	action;

}	t_keydata;

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
	t_key 		keydata;
}	t_game;

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