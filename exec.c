/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:26:21 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/10 15:12:41 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_map(void *pixel)
{
	t_game	*game;

	game = pixel;
	mlx_destroy_image(game->mlx, &game->img);
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
	move(game, 0, 0);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

static void	get_angle(t_game *game)
{
	char	direction;

	printf("map2d=%p\n", game->mapdata.map2d);
	direction = game->mapdata.map2d[game->mapdata.p_y][game->mapdata.p_x];
	if (direction == 'N')
		game->player.angle = 3 * M_PI / 2;
	if (direction == 'S')
		game->player.angle = M_PI / 2;
	if (direction == 'E')
		game->player.angle = 0;
	if (direction == 'W')
		game->player.angle = M_PI;
	game->player.fov_radians = FOV * M_PI / 180;
	game->player.player_x = (game->mapdata.p_x * TILE_SIZE) + TILE_SIZE / 2;
	game->player.player_y = (game->mapdata.p_y * TILE_SIZE) + TILE_SIZE / 2;
}

typedef int (*hook)(int, void*);
typedef int (*loop_hook)(void*);

int	execution(t_game *game)
{
	// check to see if the map within the limits, and if not, free the map;
	// check for loading textures;
	get_angle(game);
	mlx_key_hook(game->mlx, (hook)key_press, &game);

	mlx_loop_hook(game->mlx, (loop_hook)draw_map, &game);
	mlx_loop(game->mlx);
	ft_exit(game);
	return (0);
}
