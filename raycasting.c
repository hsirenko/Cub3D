/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:39:23 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/11 16:59:05 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	hit_the_wall(float x, float y, t_game *game)
{
	int	map_y;
	int	map_x;

	if (x < 0 || y < 0)
		return (0);
	map_y = floor(y);
	map_x = floor(x);
	if (map_y >= game->mapdata.map_h || map_x >= game->mapdata.map_w)
		return (0);
	if (game->mapdata.map2d[map_y] && map_x <= \
		(int)ft_strlen(game->mapdata.map2d[map_y]))
	{
		if (game->mapdata.map2d[map_y][map_x] == '1')
			return (0);
	}
	return (1);
}

static int	check_inters(float angle, float *inters, float *step, int is_horz)
{
	if (is_horz)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inters += 1;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > (M_PI / 2) && angle < (3 * M_PI / 2)))
		{
			*inters += 1;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

static float	get_hor_inters(t_game *game, float angle)
{
	int		direction;
	float	hor_x;
	float	hor_y;
	float	step_x;
	float	step_y;

	direction = check_inters(angle, &hor_y, &step_y, 1);
	step_x = 1 / tan(angle);
	step_y = 1;
	hor_y = floor(game->player.player_y);
	hor_x = game->player.player_x + \
		(hor_y - game->player.player_y) / tan(angle);
	if ((unit_circle(angle, 'y') && step_x > 0)\
		|| (!unit_circle(angle, 'y') && step_x < 0))
		step_x *= -1;
	while (hit_the_wall(hor_x, hor_y - direction, game))
	{
		hor_x += step_x;
		hor_y += step_y;
	}
	game->ray.hrz_y = hor_y;
	game->ray.hrz_x = hor_x;
	return (sqrt(pow(hor_x - game->player.player_x, 2) \
			+ pow(hor_y - game->player.player_y, 2)));
}

static float	get_vert_inters(t_game *game, float angle)
{
	int		direction;
	float	vert_x;
	float	vert_y;
	float	step_x;
	float	step_y;

	vert_y = 0.0;
	direction = check_inters(angle, &vert_x, &step_x, 0);
	step_x = 1;
	step_y = tan(angle);
	vert_x = floor(game->player.player_x);
	vert_y = game->player.player_y
		+ (vert_x - game->player.player_x) * tan(angle);
	if ((unit_circle(angle, 'x') && step_y < 0) \
		|| (!unit_circle(angle, 'x') && step_y > 0))
		step_y *= -1;
	while (hit_the_wall(vert_x - direction, vert_y, game))
	{
		vert_x += step_x;
		vert_y += step_y;
	}
	game->ray.vrt_x = vert_x;
	game->ray.vrt_y = vert_y;
	return (sqrt(pow(vert_x - game->player.player_x, 2)
			+ pow(vert_y - game->player.player_y, 2)));
}

void	ray_casting(t_game *game)
{
	double	hor_inters;
	double	ver_inters;
	int		ray_counter;

	ray_counter = 0;
	game->player.fov_radians = FOV * M_PI / 180;
	game->ray.ray_angle = game->player.angle \
			- (game->player.fov_radians / 2);
	while (ray_counter < SCREEN_WIDTH)
	{
		game->ray.flag = 0;
		hor_inters = get_hor_inters(game, nor_angle(game->ray.ray_angle));
		ver_inters = get_vert_inters(game, nor_angle(game->ray.ray_angle));
		if (hor_inters >= ver_inters)
			game->ray.dist = ver_inters;
		else
		{
			game->ray.dist = hor_inters;
			game->ray.flag = 1;
		}
		render_wall(game, ray_counter);
		ray_counter++;
		game->ray.ray_angle += (game->player.fov_radians / SCREEN_WIDTH);
	}
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
