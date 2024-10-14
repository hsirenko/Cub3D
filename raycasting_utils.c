/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:09:54 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/14 20:10:17 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	unit_dir_vector(float angle)
{
	return (rotate_vec(vec2f(0, -1), angle));
}

t_vec2f	vec2f_mulf(t_vec2f v, float f)
{
	v.x *= f;
	v.y *= f;
	return (v);
}

t_direction	detect_face(t_vec2f step)
{
	if (step.x == 1)
		return (DIRECTION_WEST);
	if (step.x == -1)
		return (DIRECTION_EAST);
	if (step.y == 1)
		return (DIRECTION_SOUTH);
	return (DIRECTION_NORTH);
}

float	distance(t_vec2f a, t_vec2f b)
{
	return (hypot(a.x - b.x, a.y - b.y));
}

float	get_local_x(t_vec2f point, t_direction face)
{
	if (face == DIRECTION_EAST)
		return (ceil(point.y) - point.y);
	if (face == DIRECTION_WEST)
		return (point.y - floor(point.y));
	if (face == DIRECTION_SOUTH)
		return (point.x - floor(point.x));
	return (ceil(point.x) - point.y);
}
