/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:09:54 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/15 17:27:36 by hsirenko         ###   ########.fr       */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:09:54 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/15 14:11:53 by kseniakarem      ###   ########.fr       */
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
		return (DIRECTION_NORTH);
	if (step.x == -1)
		return (DIRECTION_SOUTH);
	if (step.y == 1)
		return (DIRECTION_WEST);
	return (DIRECTION_EAST);
}

float	distance(t_vec2f a, t_vec2f b)
{
	return (hypot(a.x - b.x, a.y - b.y));
}

float	get_local_x(t_vec2f point, t_direction face)
{
	if (face == DIRECTION_SOUTH)
		return (ceil(point.y) - point.y);
	if (face == DIRECTION_NORTH)
		return (point.y - floor(point.y));
	if (face == DIRECTION_WEST)
		return (point.x - floor(point.x));
	if (face == DIRECTION_EAST)
		return (ceil(point.x) - point.x);
	return (ceil(point.x) - point.x);
}
