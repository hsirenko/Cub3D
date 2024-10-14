/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:39:23 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/14 20:24:54 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_hit	hit(t_ray ray, t_vec2f point, t_vec2f step)
{
	t_hit	hit;

	hit.angle = ray.angle;
	hit.distance = distance(point, ray.origin);
	hit.face = detect_face(step);
	hit.hit = 1;
	hit.local_x = get_local_x(point, hit.face);
	return (hit);
}

t_hit	no_hit(void)
{
	t_hit	hit;

	hit.hit = 0;
	hit.distance = 10000000;
	hit.face = DIRECTION_NORTH;
	hit.angle = 0;
	hit.local_x = 0;
	return (hit);
}

t_hit	cast(t_mapdata *map, t_ray ray, t_vec2f start, t_vec2f step)
{
	t_vec2f	pos;
	int		i;

	i = 0;
	pos = start;
	while (i < map->map_h || i < map->map_w)
	{
		if (inside_wall(map, vec2f_add(pos, vec2f_mulf(step, 1e-6))))
			return (hit(ray, pos, step));
		pos = vec2f_add(pos, step);
		i++;
	}
	return (no_hit());
}

t_hit	cast_ray(t_mapdata *map, t_ray ray)
{
	t_hit	hor_hit;
	t_hit	ver_hit;

	hor_hit = cast(map, ray, first_hor_inters(ray), hor_step(ray));
	ver_hit = cast(map, ray, first_vert_inters(ray), vert_step(ray));
	if (!hor_hit.hit && !ver_hit.hit)
		return (no_hit());
	if (!hor_hit.hit)
		return (ver_hit);
	if (!ver_hit.hit)
		return (hor_hit);
	if (hor_hit.distance < ver_hit.distance)
		return (hor_hit);
	return (ver_hit);
}

void	ray_casting(t_game *game)
{
	int		ray_counter;
	t_ray	ray;
	t_hit	hit;

	ray_counter = 0;
	game->player.fov_radians = FOV * M_PI / 180;
	ray.origin = vec2f(game->player.player_x, game->player.player_y);
	ray.angle = game->player.angle - (game->player.fov_radians / 2);
	while (ray_counter < SCREEN_WIDTH)
	{
		hit = cast_ray(&game->mapdata, ray);
		render_wall(game, ray_counter, hit);
		ray_counter++;
		ray.angle += (game->player.fov_radians / SCREEN_WIDTH);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
