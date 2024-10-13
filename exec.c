/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:26:21 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/13 17:25:39 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_map(void *pixel)
{
	t_game	*game;

	game = pixel;
	ray_casting(game);
}

static void	get_angle(t_game *game)
{
	char	direction;

	direction = game->mapdata.map2d[(int)game->player.player_y][(int)game->player.player_x];
	if (direction == 'N')
		game->player.angle = 3 * M_PI / 2;
	if (direction == 'S')
		game->player.angle = M_PI / 2;
	if (direction == 'E')
		game->player.angle = 0;
	if (direction == 'W')
		game->player.angle = M_PI;
	game->player.fov_radians = FOV * M_PI / 180;
}

typedef int (*hook)(int, void*);
typedef int (*loop_hook)(void*);

int	execution(t_game *game)
{
	// check to see if the map within the limits, and if not, free the map;
	// check for loading textures;
	get_angle(game);
	mlx_key_hook(game->win, (hook)key_press, game);
	// mlx_loop_hook(game->mlx, (loop_hook)draw_map, game);
	draw_map(game);
	mlx_loop(game->mlx);
	ft_exit(game);
	return (0);
}
