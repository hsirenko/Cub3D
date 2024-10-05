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

void draw_floor_ceiling(t_game *game, t_img* img) // draw the floor and the ceiling
{
 int  i =0;
 int x = 0;

	while (i < SCREEN_HEIGHT/2)
    {
        while(x<=SCREEN_WIDTH)
		    my_mlx_pixel_put(img, x++, i, game->color_floor); // floor
        x = 0;
        i++;
    }
	while (i < SCREEN_HEIGHT)
	    {
        while(x<=SCREEN_WIDTH)
		    my_mlx_pixel_put(img, x++, i, game->color_ceiling); // floor
        x = 0;
        i++;
    }
}
