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

void	draw_wall(t_game * game, int ray_counter, int t_pix, int b_pix)	// draw the wall
{
	int colour;
	printf("top=%d bottom=%d\n", t_pix, b_pix);

	colour = get_colour(game);
	while (t_pix < b_pix)
		my_mlx_pixel_put(&game->img, ray_counter, t_pix++, colour);
}

void render_wall(t_game *game, int ray_counter) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	game->ray.dist *= cos(nor_angle(game->ray.ray_angle - game->player.angle)); // fix the fisheye
	wall_h = (1. / game->ray.dist) * ((SCREEN_WIDTH / 2) / tan(game->player.fov_radians / 2)); // get the wall height
	// printf("dist=%f wall_h=%f\n", game->ray.dist, wall_h);
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix >SCREEN_HEIGHT) // check the bottom pixel
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_floor_ceiling(game, ray_counter, t_pix, b_pix); // draw the floor and the ceiling
	draw_wall(game, ray_counter, t_pix, b_pix); // draw the wall
}