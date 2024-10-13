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

t_image	*get_texture(t_game *game, t_direction face)
{
	if (face == DIRECTION_EAST)
		return &game->mapdata.east_wall;
	if (face == DIRECTION_WEST)
		return &game->mapdata.west_wall;
	if (face == DIRECTION_SOUTH)
		return &game->mapdata.south_wall;
	return &game->mapdata.north_wall;
}

int get_colour(t_direction face)
{
	if (face == DIRECTION_EAST)
		return PSYCHEDELIC_PINK;
	if (face == DIRECTION_WEST)
		return PURPLE;
	if (face == DIRECTION_SOUTH)
		return PSYCHEDELIC_LIME;
	return BLUE;
}

unsigned int my_mlx_pixel_get(t_image img, int x, int y) {
	int bits_per_pixel, line_size, endian;
	char* addr = mlx_get_data_addr(img.img, &bits_per_pixel, &line_size, &endian);
	return *(unsigned int*)(&addr[y * line_size + x * bits_per_pixel / 8]);
}

void	draw_wall(t_game * game, int ray_counter, int t_pix, int b_pix, t_hit hit)	// draw the wall
{
	double			x_o;
	double			y_o;
	t_image	*texture;
	double			factor;

	texture = get_texture(game, hit.face);
	double wall_h = (1. / hit.distance) * ((SCREEN_WIDTH / 2) / tan(game->player.fov_radians / 2)); // get the wall height b_pix - t_pix;
	factor = (double)texture->img_h / wall_h;
	x_o = hit.local_x * texture->img_w;
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

void render_wall(t_game *game, int ray_counter, t_hit hit) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	hit.distance *= cos(nor_angle(hit.angle - game->player.angle)); // fix the fisheye
	wall_h = (1. / hit.distance) * ((SCREEN_WIDTH / 2) / tan(game->player.fov_radians / 2)); // get the wall height
	// printf("dist=%f wall_h=%f\n", game->ray.dist, wall_h);
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix >SCREEN_HEIGHT) // check the bottom pixel
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_floor_ceiling(game, ray_counter, t_pix, b_pix); // draw the floor and the ceiling
	draw_wall(game, ray_counter, t_pix, b_pix, hit); // draw the wall
}