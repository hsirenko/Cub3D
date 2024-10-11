#include "cub3D.h"

void my_mlx_pixel_put(t_img* img, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
    unsigned int* pixel_addr = (unsigned int*)(img->addr + img->line_length * y + img->bpp/8 * x);
    *pixel_addr = color;
}

void draw_floor_ceiling(t_game *game, int ray_counter, int t_pix, int b_pix) // draw the floor and the ceiling
{
 int  i =b_pix;

	while (i < SCREEN_HEIGHT)
    {
        my_mlx_pixel_put(&game->img, ray_counter, i++, game->color_floor); // floor
    }
	i=0;
	while (i < t_pix)
		my_mlx_pixel_put(&game->img, ray_counter, i++, game->color_ceiling);
}


t_image	*get_texture(t_game *game)
{
	game->ray.ray_angle = nor_angle(game->ray.ray_angle);
	if (game->ray.flag == 0)
	{
		if (game->ray.ray_angle > M_PI / 2 && game->ray.ray_angle < 3 * (M_PI / 2))
			return(&game->mapdata.east_wall);
		else
			return(&game->mapdata.west_wall);
	}
	else
	{
		if (game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI)
			return(&game->mapdata.south_wall);
		else
			return(&game->mapdata.north_wall);
	}
}

int get_colour(t_game *game)
{
	game->ray.ray_angle = nor_angle(game->ray.ray_angle);
	if (game->ray.flag == 0)
	{
		if (game->ray.ray_angle > M_PI / 2 && game->ray.ray_angle < 3 * (M_PI / 2))
			return(PSYCHEDELIC_PINK); //ea
		else
			return(PURPLE);//we
	}
	else
	{
		if (game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI)
			return(PSYCHEDELIC_LIME);//so
		else
			return(BLUE);//no
	}
}

double	get_x_o(t_image	*texture, t_game *game)
{
	double	x_o;

	if (game->ray.flag == 1)
		x_o = (int)fmodf((game->ray.hrz_x * \
		(texture->img_w / TILE_SIZE)), texture->img_w);
	else
		x_o = (int)fmodf((game->ray.vrt_y * \
		(texture->img_w / TILE_SIZE)), texture->img_w);
	return (x_o);
}

unsigned int my_mlx_pixel_get(t_image img, int x, int y) {
	int bits_per_pixel, line_size, endian;
	char* addr = mlx_get_data_addr(img.img, &bits_per_pixel, &line_size, &endian);
	return *(unsigned int*)(&addr[y * line_size + x * bits_per_pixel / 8]);
}

void	draw_wall(t_game * game, int ray_counter, int t_pix, int b_pix, double wall_h)	// draw the wall
{
	double			x_o;
	double			y_o;
	t_image	*texture;
	double			factor;

	texture = get_texture(game);
	factor = (double)texture->img_h / wall_h;
	x_o = get_x_o(texture, game);
	y_o = (t_pix - (SCREEN_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(&game->img, ray_counter, t_pix, my_mlx_pixel_get(*texture, x_o, y_o));
		y_o += factor;
		t_pix++;
	}
}

void render_wall(t_game *game, int ray_counter) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

(void)ray_counter;
	game->ray.dist *= cos(nor_angle(game->ray.ray_angle - game->player.angle)); // fix the fisheye
	wall_h = (TILE_SIZE / game->ray.dist) * ((SCREEN_WIDTH / 2) / tan(game->player.fov_radians / 2)); // get the wall height
	// printf("dist=%f wall_h=%f\n", game->ray.dist, wall_h);
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix >SCREEN_HEIGHT) // check the bottom pixel
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_floor_ceiling(game, ray_counter, t_pix, b_pix); // draw the floor and the ceiling
	draw_wall(game, ray_counter, t_pix, b_pix, wall_h); // draw the wall
}