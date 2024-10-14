/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:39:53 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/14 20:36:17 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	inside_wall(t_mapdata *map, t_vec2f pos)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	if (x < 0 || y < 0 || x >= map->map_w || y >= map->map_h)
		return (0);
	return (map->map2d[y][x] == '1');
}

void	handle_key_input(int key, t_game *game, t_vec2f *translation)
{
	t_vec2f	speed;

	speed = vec2f(0, -0.2);
	if (key == KEY_ESC)
		ft_exit(game);
	else if (key == 'a')
		*translation = rotate_vec(speed, game->player.angle - M_PI / 2);
	else if (key == 'd')
		*translation = rotate_vec(speed, game->player.angle + M_PI / 2);
	else if (key == 's')
		*translation = rotate_vec(speed, game->player.angle + M_PI);
	else if (key == 'w')
		*translation = rotate_vec(speed, game->player.angle);
	else if (key == KEY_LEFT)
		game->player.angle -= DELTA_ANGLE;
	else if (key == KEY_RIGHT)
		game->player.angle += DELTA_ANGLE;
}

void	key_press(int key, void *game_void)
{
	t_game	*game;
	t_vec2f	translation;
	t_vec2f	pos;

	game = game_void;
	translation = vec2f(0, 0);
	handle_key_input(key, game, &translation);
	pos = vec2f(game->player.player_x, game->player.player_y);
	pos = vec2f_add(pos, translation);
	if (!inside_wall(&game->mapdata, pos))
	{
		game->player.player_x = pos.x;
		game->player.player_y = pos.y;
	}
	draw_map(game);
}
