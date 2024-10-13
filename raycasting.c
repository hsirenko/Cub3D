/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:39:23 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/13 17:44:00 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_hit cast_ray(t_mapdata* map, t_ray ray) {
	(void)map;
	t_hit hit;
	hit.distance = 10;
	hit.face = DIRECTION_SOUTH;
	hit.hit = 1;
	hit.angle = ray.angle;
	return hit;
}

void	ray_casting(t_game *game)
{
	int		ray_counter;

	ray_counter = 0;
	game->player.fov_radians = FOV * M_PI / 180;

	t_ray ray;
	ray.start = vec2f(game->player.player_x, game->player.player_y);
	ray.angle = game->player.angle - (game->player.fov_radians / 2);
	
	while (ray_counter < SCREEN_WIDTH)
	{
		t_hit hit = cast_ray(&game->mapdata, ray);
		render_wall(game, ray_counter, hit);
		ray_counter++;
		ray.angle += (game->player.fov_radians / SCREEN_WIDTH);
	}
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
