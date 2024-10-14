/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:35:56 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/14 20:36:22 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	vec2f(float x, float y)
{
	t_vec2f	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec2f	rotate_vec(t_vec2f vec, float angle)
{
	t_vec2f	res;

	res.x = vec.x * cos(angle) - vec.y * sin(angle);
	res.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (res);
}

t_vec2f	vec2f_add(t_vec2f a, t_vec2f b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}
