/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:39:23 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/13 18:21:26 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f unit_direction_vector(float angle) {
	return rotate_vec(vec2f(0, -1), angle);
}

t_vec2f first_horizontal_intersection(t_ray ray) {
	t_vec2f direction = unit_direction_vector(ray.angle);
	t_vec2f res;
	res.y = floor(ray.origin.y);
	if (direction.y == 0)
		return ray.origin;
	if (direction.y > 0)
		res.y++;
	res.x = ray.origin.x + (res.y - ray.origin.y) * direction.x / direction.y;
	return res;
}

t_vec2f first_vertical_intersection(t_ray ray) {
	t_vec2f direction = unit_direction_vector(ray.angle);
	t_vec2f res;
	res.x = floor(ray.origin.x);
	if (direction.x == 0)
		return ray.origin;
	if (direction.x > 0)
		res.x++;
	res.y = ray.origin.y + (res.x - ray.origin.x) * direction.y / direction.x;
	return res;
}

t_vec2f horizontal_step(t_ray ray) {
	t_vec2f dir = unit_direction_vector(ray.angle);
	if (dir.y == 0)
		return vec2f(dir.x, 0);
	dir.x /= fabs(dir.y);
	dir.y /= fabs(dir.y);
	return dir;
}

t_vec2f vertical_step(t_ray ray) {
	t_vec2f dir = unit_direction_vector(ray.angle);
	if (dir.x == 0)
		return vec2f(0, dir.y);
	dir.y /= fabs(dir.x);
	dir.x /= fabs(dir.x);
	return dir;
}

t_vec2f vec2f_mulf(t_vec2f v, float f) {
	v.x *= f;
	v.y *= f;
	return v;
}

t_direction detect_face(t_vec2f step) {
	if (step.x == 1)
		return DIRECTION_WEST;
	if (step.x == -1)
		return DIRECTION_EAST;
	if (step.y == 1)
		return DIRECTION_SOUTH;
	return DIRECTION_NORTH;
}

float distance(t_vec2f a, t_vec2f b) {
	return hypot(a.x - b.x, a.y - b.y);
}

t_hit hit(t_ray ray, t_vec2f point, t_vec2f step) {
	t_hit hit;
	hit.angle = ray.angle;
	hit.distance = distance(point, ray.origin);
	hit.face = detect_face(step);
	hit.hit = 1;
	return hit;
}

t_hit no_hit() {
	t_hit hit;
	hit.hit = 0;
	hit.distance = 10000000;
	hit.face = DIRECTION_NORTH;
	hit.angle = 0;
	return hit;
}

t_hit cast(t_mapdata* map, t_ray ray, t_vec2f start, t_vec2f step) {
	t_vec2f pos = start;
	int i = 0;
	while(i < map->map_h || i < map->map_w) {
		if (inside_wall(map, vec2f_add(pos, vec2f_mulf(step, 1e-6))))
			return  hit(ray, pos, step);
		pos = vec2f_add(pos, step);
		i++;
	}
	return no_hit();
}

t_hit cast_ray(t_mapdata* map, t_ray ray) {
	t_hit hor_hit = cast(map, ray, first_horizontal_intersection(ray), horizontal_step(ray));
	t_hit ver_hit = cast(map, ray, first_vertical_intersection(ray), vertical_step(ray));
	
	if (!hor_hit.hit && !ver_hit.hit)
		return no_hit();
	if (!hor_hit.hit)
		return ver_hit;
	if (!ver_hit.hit)
		return hor_hit;
	if (hor_hit.distance < ver_hit.distance) 
		return hor_hit;
	return ver_hit;
}

void	ray_casting(t_game *game)
{
	int		ray_counter;

	ray_counter = 0;
	game->player.fov_radians = FOV * M_PI / 180;

	t_ray ray;
	ray.origin = vec2f(game->player.player_x, game->player.player_y);
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
