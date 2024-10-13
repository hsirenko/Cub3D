/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:39:53 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/13 18:42:33 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f vec2f(float x, float y) {
	t_vec2f vec;
	vec.x = x;
	vec.y = y;
	return vec;
}

t_vec2f rotate_vec(t_vec2f vec, float angle) {
	t_vec2f res;
	res.x = vec.x * cos(angle) - vec.y * sin(angle);
	res.y = vec.x * sin(angle) + vec.y * cos(angle);
	return res;
}

t_vec2f vec2f_add(t_vec2f a, t_vec2f b) {
	a.x += b.x;
	a.y += b.y;
	return a;
}

int inside_wall(t_mapdata* map, t_vec2f pos) {
	int x = pos.x;
	int y = pos.y;
	if (x < 0 || y < 0 || x >= map->map_w || y >= map->map_h) {
		return 0;
	}
	
	return map->map2d[y][x] == '1';
}

#define DELTA_ANGLE 0.1

void	key_press(int key, void *game_void)
{
	t_game	*game;

	game = game_void;

	t_vec2f translation = vec2f(0,0);
	t_vec2f speed = vec2f(0, -0.2);

	if (key == MLX_KEY_ESCAPE)
		ft_exit(game);
	else if (key == 'a')
		translation = rotate_vec(speed, game->player.angle - M_PI/2);
	else if (key == 'd')
		translation = rotate_vec(speed, game->player.angle + M_PI/2);
	else if (key == 's')
		translation = rotate_vec(speed, game->player.angle + M_PI);
	else if (key == 'w')
		translation = rotate_vec(speed, game->player.angle);
	else if (key == 'k')
		game->player.angle -= DELTA_ANGLE;
	else if (key == 'l')
		game->player.angle += DELTA_ANGLE;

	t_vec2f pos = vec2f(game->player.player_x, game->player.player_y);
	pos = vec2f_add(pos, translation);
	if (!inside_wall(&game->mapdata, pos)) {
		game->player.player_x = pos.x;
		game->player.player_y = pos.y;
	}

	draw_map(game);
}