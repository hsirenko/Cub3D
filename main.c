/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:04:32 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/07 17:09:38 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int main(int argc, char **argv)
{
    (void)argc;
    t_game  game;

    init_struct_game(&game, argv[1]);//parsing
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_length, &game.img.endian);
    
    //my_mlx_pixel_put(&game.img, x, y, RED);

    ray_casting(&game);
    //draw_floor_ceiling(&game,&game.img );
    mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
    mlx_loop(game.mlx);
    return 0;
}

