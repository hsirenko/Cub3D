/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:04:32 by helensirenk       #+#    #+#             */
/*   Updated: 2024/09/24 12:05:50 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
//     char *dst;

//     dst = img->addr + (y * img->line_length + x * (img->bpp / 8));

//     *(unsigned int *)dst = color;
// }

// static void	draw_ceiling_and_floor(t_game *game)
// {
// 	unsigned int	*dst;
// 	unsigned int	i;

// 	dst = (unsigned int *) game->img.addr;
// 	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
// 	while (--i > 0)
// 		*dst++ = game->color_ceiling;
// 	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
// 	while (--i > 0)
// 		*dst++ = game->color_floor;
// }

// static void    init_struct_game(t_game *game)
// {
//     game->color_ceiling = BLUE;
//     game->color_floor = PSYCHEDELIC_CYAN;
// }

int main() //(int **argc, char **argv)
{
    //t_img  *img;
    t_game  *game;
   void *mlx_win;

    game = malloc(sizeof(t_game));

    init_struct_game(game);
    game->mlx = mlx_init();
    mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
    //my_mlx_pixel_put(img, 5, 5, RED);
    draw_ceiling_and_floor(game);
    mlx_put_image_to_window(game->mlx, mlx_win, game->img.img, 0, 0);
    mlx_loop(game->mlx);
}

