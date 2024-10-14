/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_inters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:41:28 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/14 20:09:12 by helensirenk      ###   ########.fr       */
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

	if (dir.y == 0)
		return (vec2f(dir.x, 0));
	dir = unit_dir_vector(ray.angle);
	dir.x /= fabs(dir.y);
	dir.y /= fabs(dir.y);
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
