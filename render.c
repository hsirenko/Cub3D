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


// void draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
// {
//  int  i;
//  int  c;

// 	i = b_pix;
// 	while (i < SCREEN_HEIGHT)
// 		my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // floor
// 	i = 0;
// 	while (i < t_pix)
// 		my_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF); // ceiling
// }

// int get_color(t_mlx *mlx, int flag) // get the color of the wall
// {
// 	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normalize the angle
// 	if (flag == 0)
// 	{
// 		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
// 			return (0xB5B5B5FF); // west wall
// 		else
// 			return (0xB5B5B5FF); // east wall
// 	}
// 	else
// 	{
// 		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
// 			return (0xF5F5F5FF); // south wall
// 		else
// 			return (0xF5F5F5FF); // north wall
// 	}
// }

// void draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix) // draw the wall
// {
// 	int color;

// 	color = get_color(mlx, mlx->ray->flag);
// 	while (t_pix < b_pix)
// 		my_mlx_pixel_put(mlx, ray, t_pix++, color);
// }

// void render_wall(t_mlx *mlx, int ray) // render the wall
// {
// 	double wall_h;
// 	double b_pix;
// 	double t_pix;

// 	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye
// 	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
// 	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
// 	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
// 	if (b_pix > SCREEN_HEIGHT) // check the bottom pixel
// 		b_pix = SCREEN_HEIGHT;
// 	if (t_pix < 0) // check the top pixel
// 		t_pix = 0;
// 	draw_wall(mlx, ray, t_pix, b_pix); // draw the wall
// 	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
// }