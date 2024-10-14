/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:26:21 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/14 19:04:37 by helensirenk      ###   ########.fr       */
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
	int		x;
	int		y;

	x = (int)game->player.player_x;
	y = (int)game->player.player_y;
	direction = game->mapdata.map2d[y][x];
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

int	execution(t_game *game)
{
	get_angle(game);
	mlx_key_hook(game->win, (t_hook)(&key_press), game);
	mlx_hook(game->win, 17, 0, (t_hook)(&ft_exit), game);
	draw_map(game);
	mlx_loop(game->mlx);
	ft_exit(game);
	return (0);
}
