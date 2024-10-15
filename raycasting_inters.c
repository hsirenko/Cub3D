/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_inters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:41:28 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/15 18:38:28 by hsirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	first_hor_inters(t_ray ray)
{
	t_vec2f	direction;
	t_vec2f	res;

	res.y = floor(ray.origin.y);
	direction = unit_dir_vector(ray.angle);
	if (direction.y == 0)
		return (ray.origin);
	if (direction.y > 0)
		res.y++;
	res.x = ray.origin.x + (res.y - ray.origin.y) * direction.x / direction.y;
	return (res);
}

t_vec2f	first_vert_inters(t_ray ray)
{
	t_vec2f	direction;
	t_vec2f	res;

	res.x = floor(ray.origin.x);
	direction = unit_dir_vector(ray.angle);
	if (direction.x == 0)
		return (ray.origin);
	if (direction.x > 0)
		res.x++;
	res.y = ray.origin.y + (res.x - ray.origin.x) * direction.y / direction.x;
	return (res);
}

t_vec2f	hor_step(t_ray ray)
{
	t_vec2f	dir;

	dir = unit_dir_vector(ray.angle);
	if (dir.y == 0)
		return (vec2f(dir.x, 0));
	dir.x /= fabs(dir.y);
	dir = unit_dir_vector(ray.angle);
	return (dir);
}

t_vec2f	vert_step(t_ray ray)
{
	t_vec2f	dir;

	dir = unit_dir_vector(ray.angle);
	if (dir.x == 0)
		return (vec2f(0, dir.y));
	dir.y /= fabs(dir.x);
	dir.x /= fabs(dir.x);
	return (dir);
}
