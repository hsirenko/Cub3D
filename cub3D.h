/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:05:28 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/15 17:35:31 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define FOV 60
# define ROTATION_SPEED 0.05
# define PLAYER_SPEED 3
# define DELTA_ANGLE 0.1

/*COLORS*/
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF

# define PSYCHEDELIC_PINK 0xFF1493
# define PSYCHEDELIC_LIME 0x32CD32
# define PSYCHEDELIC_CYAN 0x00FFFF
# define PSYCHEDELIC_YELLOW 0xFFFF00
# define PSYCHEDELIC_PURPLE 0x9400D3

typedef int		(*t_hook)(int, void *);
typedef int		(*t_loop_hook)(void *);

typedef enum action
{
	PRESS = 1,
	RELEASE = 0,
	REPEAT = 2,
}				t_action;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;

}				t_img;

typedef struct s_image
{
	void		*img;
	int			img_h;
	int			img_w;
}				t_image;

typedef struct s_mapdata
{
	char		**map2d;
	char		**map_check;
	int			p_x;
	int			p_y;
	int			map_h;
	int			map_w;
	t_image		north_wall;
	t_image		south_wall;
	t_image		east_wall;
	t_image		west_wall;
}				t_mapdata;

typedef struct s_player
{
	double		player_x;
	double		player_y;
	char		start_orient;
	double		angle;
	float		fov_radians;
}				t_player;

typedef struct s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct s_ray
{
	t_vec2f		origin;
	double		angle;
}				t_ray;

typedef enum e_direction
{
	DIRECTION_NORTH,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_EAST,
}				t_direction;

typedef struct s_string
{
	int			len;
	int			cap;
	char		*data;
}				t_string;

typedef struct s_hit
{
	int			hit;
	double		distance;
	t_direction	face;
	float		angle;
	float		local_x;
}				t_hit;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_mapdata	mapdata;
	int			color_floor;
	int			color_ceiling;
	t_img		img;
	t_player	player;
}				t_game;

typedef enum e_key
{
	KEY_ESC = 65307,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
}				t_key;

typedef struct s_pix
{
	double		b_pix;
	double		t_pix;
}				t_pix;

typedef struct s_parser_state
{
	int			i;
	int			j;
	int			c;
	int			player_count;
	char		*src;
	char		player;
}				t_parser_state;

typedef struct s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct s_stack
{
	int			len;
	int			cap;
	t_coord		*data;
}				t_stack;

int				inside_wall(t_mapdata *map, t_vec2f pos);

//raycasting
t_vec2f			vec2f(float x, float y);
t_vec2f			rotate_vec(t_vec2f vec, float angle);
t_vec2f			vec2f_add(t_vec2f a, t_vec2f b);

t_direction		detect_face(t_vec2f step);
t_vec2f			first_hor_inters(t_ray ray);
t_vec2f			first_vert_inters(t_ray ray);
t_vec2f			hor_step(t_ray ray);
t_vec2f			vert_step(t_ray ray);
t_vec2f			unit_dir_vector(float angle);
t_vec2f			vec2f_mulf(t_vec2f v, float f);
float			distance(t_vec2f a, t_vec2f b);
float			get_local_x(t_vec2f point, t_direction face);
t_hit			hit(t_ray ray, t_vec2f point, t_vec2f step);
t_hit			no_hit(void);
t_hit			cast(t_mapdata *map, t_ray ray, t_vec2f start, t_vec2f step);
t_hit			cast_ray(t_mapdata *map, t_ray ray);
void			ray_casting(t_game *game);

int				hit_the_wall(float x, float y, t_game *game);
void			render_wall(t_game *game, int ray_counter, t_hit hit);

//player movements
void			key_press(int key, void *game_void);
void			rotate(t_game *game, int i);
void			move(t_game *game, double move_x, double move_y);
void			hook_move_rotate(t_game *game, double move_x, double move_y);
void			handle_key_input(int key, t_game *game, t_vec2f *translation);

//utils
int				unit_circle(float angle, char c);
float			nor_angle(float angle);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			ft_exit(t_game *game);
char			*cut_string(char *string, int n);
void			panic(char *msg);

// check_map
int				has_holes(t_mapdata map, t_player player);

//exec
int				execution(t_game *game);
void			draw_map(void *pixel);

//vector_utils
t_vec2f			vec2f(float x, float y);
t_vec2f			rotate_vec(t_vec2f vec, float angle);
t_vec2f			vec2f_add(t_vec2f a, t_vec2f b);

//parsing
t_string		string_with_capacity(int cap);
t_string		string_grow(t_string s, int new_cap);
int				get_map_height(char *inp_string);
int				get_map_width(char *inp_string);
int				check(char c, char *str);
void			find_angle_view(t_game *game, const char c);
char			*read_file(int fd);
int				fill_map(t_game *game, char *src);
int				get_map(t_game *game, char **inp_string);
int				parse(t_game *game, int fd);
void			init_struct_game(t_game *game, char *file_name);
int				parse_byte_n(char *s, int n);
int				index_of(char *s, char c);
int				read_color(char **str, char sep);
int				read_colors(char **str);
int				get_colors(t_game *game, char **inp_string);
int				find_prefix(char *prefix, char *string);
char			*trim_str(int len, char *str);
int				parse_path(void *mlx, char *direction, char **inp_string,
					t_image *img);
int				get_wall_img(t_game *game, char **inp_string);
int				check_gamer(char gamer, int gamer_count);
t_parser_state	new_parser_state(char *src);
int				has_chars(t_parser_state s);
int				parse_newline(t_parser_state *s);
int				parse_newline(t_parser_state *s);
void			advance(t_parser_state *s);
char			current_char(t_parser_state s);
int				parse_player(t_parser_state *s);
void			parse_wall_or_player(t_parser_state *s, t_game *game);
void			fill_neighbours_of(t_coord curr, t_coord *neighbours);
int				_has_holes(t_mapdata map, t_stack *stack, char *visited);
t_coord			new_coord(int x, int y);
void			push(t_stack *stack, t_coord coord);
t_stack			make_stack(int capacity);
int				pop(t_stack *stack, t_coord *dst);

//render
t_image			*get_texture(t_game *game, t_direction face);
int				get_colour(t_direction face);
unsigned int	my_mlx_pixel_get(t_image img, int x, int y);
void			render_wall(t_game *game, int ray_counter, t_hit hit);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			draw_floor_ceiling(t_game *game, int ray_counter, t_pix pix);

#endif