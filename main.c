/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:04:32 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/10 15:22:53 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
    (void)argc;
    t_game  game;

    game.mlx = mlx_init();
    printf("mlx=%p\n", game.mlx);
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    init_struct_game(&game, argv[1]);
    //game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    //game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
    //my_mlx_pixel_put(img, 5, 5, RED);
    //ray_casting(&game);
    //mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
    //mlx_loop(game.mlx);
    execution(&game);
    return (0);
}
