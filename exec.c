/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:26:21 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/09 16:25:25 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_map(void *pixel)
{
	t_game	*game;

	game = pixel;
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	move(game, 0, 0);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

static void	get_angle(t_game *game)
{
	char	direction;

	direction = game->mapdata->map2d[game->mapdata->p_y][game->mapdata->p_x];
	if (direction == 'N')
		game->player->angle = 3 * M_PI / 2;
	if (direction == 'S')
		game->player->angle = M_PI / 2;
	if (direction == 'E')
		game->player->angle = 0;
	if (direction == 'W')
		game->player->angle = M_PI;
	game->player->fov_radians = FOV * M_PI / 180;
	game->player->player_x = (game->mapdata->p_x * TILE_SIZE) + TILE_SIZE / 2;
	game->player->player_y = (game->mapdata->p_y * TILE_SIZE) + TILE_SIZE / 2;
}

int	execution(t_mapdata *mapdata_exec)
{
	t_game	game;

	// check to see if the map within the limits, and if not, free the map;
	game.mapdata = mapdata_exec;
	game.player = (t_player *)ft_calloc(sizeof(t_player), 1);
	game.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (ft_exit(&game), 0);
	// check for loading textures;
	get_angle(&game);
	mlx_key_hook(game.mlx, &key_press, &game);
	mlx_loop_hook(game.mlx, &draw_map, &game);
	mlx_loop(game.mlx);
	ft_exit(&game);
	return (0);
}
