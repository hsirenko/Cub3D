/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:04:32 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/07 17:47:22 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_ceiling_and_floor(t_game *game)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *) game->img.addr;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->color_ceiling;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->color_floor;
}

int main(int argc, char **argv)
{
    (void)argc;
    t_game  game;

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_length, &game.img.endian);
    
    //my_mlx_pixel_put(&game.img, x, y, RED);

    init_struct_game(&game, argv[1]);
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_length, &game.img.endian);
    //my_mlx_pixel_put(img, 5, 5, RED);
    //ray_casting(&game);
    draw_ceiling_and_floor(&game);
    mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
    mlx_loop(game.mlx);
}

