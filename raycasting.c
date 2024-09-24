/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:39:23 by helensirenk       #+#    #+#             */
/*   Updated: 2024/09/24 14:32:26 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	hit_the_wall(float x, float y, t_game *game)
{
	int	map_y;
	int	map_x;

	if (x < 0 || y < 0)
		return (0);
	map_y = floor(y / TILE_SIZE);
	map_x = floor(x / TILE_SIZE);
	if (map_y >= game->mapdata->map_h || map_x >= game->mapdata->map_w)
		return (0);
	if (game->mapdata->map2d[map_y] && map_x
		<= (int)ft_strlen(game->mapdata->map2d[map_y]))
		if (game->mapdata->map2d[map_y][map_x] == '1')
			return (0);
	return (1);
}

static int	check_inters(float angle, float *inters, float *step, int is_horz)
{
	if (is_horz)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inters += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > (M_PI / 2) && angle > (3 * M_PI / 2)))
		{
			*inters += TILE_SIZE;
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
	step_x = TILE_SIZE / tan(angle);
	step_y = TILE_SIZE;
	hor_y = floor(game->player->player_y / TILE_SIZE) * TILE_SIZE;
	hor_x = game->player->player_x
		+ (hor_y - game->player->player_y) / tan(angle);
	while (hit_the_wall(hor_x, hor_y - direction, game))
	{
		hor_x += step_x;
		hor_y += step_y;
	}
	game->ray->hrz_y = hor_y;
	game->ray->hrz_x = hor_x;
	return (sqrt(pow(hor_x - game->player->player_x, 2)
			+ pow(hor_y - game->player->player_y, 2)));
}

static float	get_vert_inters(t_game *game, float angle)
{
	int		direction;
	float	vert_x;
	float	vert_y;
	float	step_x;
	float	step_y;

	direction = check_inters(angle, &vert_x, &step_x, 0);
	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(angle);
	vert_x = floor(game->player->player_x / TILE_SIZE) * TILE_SIZE;
	vert_y = game->player->player_y
		+ (vert_y - game->player->player_x) / tan(angle);
	if ((unit_circle(angle, 'y') && step_x > 0)
		|| (!unit_circle(angle, 'x') && step_x < 0))
		step_x *= -1;
	while (hit_the_wall(vert_x - direction, vert_y, game))
	{
		vert_x += step_x;
		vert_y += step_y;
	}
	game->ray->vrt_x = vert_x;
	game->ray->vrt_y = vert_y;
	return (sqrt(pow(vert_x - game->player->player_x, 2)
			+ pow(vert_y - game->player->player_y, 2)));
}

void	ray_casting(t_game *game)
{
	double	hor_inters;
	double	ver_inters;
	int		ray_counter;

	ray_counter = 0;
	game->player->fov_radians = FOV * M_PI / 180;
	game->ray->ray_angle = game->player->angle
		- (game->player->fov_radians / 2);
	while (ray_counter < SCREEN_WIDTH)
	{
		game->ray->flag = 0;
		hor_inters = get_hor_inters(game, normalz_angle(game->ray->ray_angle));
		ver_inters = get_vert_inters(game, normalz_angle(game->ray->ray_angle));
		if (hor_inters >= ver_inters)
			game->ray->dist = ver_inters;
		else
		{
			game->ray->dist = hor_inters;
			game->ray->flag = 1;
		}
		// ksusha's function to render the walls smth like render(game, ray);
		ray_counter++;
		game->ray->ray_angle += (game->player->fov_radians / SCREEN_WIDTH);
	}
}

//Horizontal intersections: We move vertically by TILE_SIZE, and we need to calculate the horizontal distance (step_x). 
//Since tan(angle) gives us the vertical-to-horizontal ratio, we divide TILE_SIZE by tan(angle) to find the horizontal step size.

//Vertical intersections: We move horizontally by TILE_SIZE, and we need to calculate the vertical distance (step_y).
//Since tan(angle) gives us the vertical-to-horizontal ratio, we multiply TILE_SIZE by tan(angle) to find the vertical step size.

// int main()
// {
// 	float angle1 = 45;
// 	float inters = 0.0;
// 	float step = TILE_SIZE;
// 	printf("Before: inter = %.2f, step = %.2f\n", inters, step);
// 	int result = check_inters(angle1, &inters, &step, 1);
// 	printf("After: inter = %.2f, step = %.2f, result = %d\n", inters, step, result);
// 	//Result: Move to the next tile upwards.

// 	inters = 0.0;
// 	step = TILE_SIZE;
// 	float angle2 = 5 * M_PI / 4; // 225 degrees, points down;
// 	printf("Before: inter = %.2f, step = %.2f\n", inters, step);
// 	int result2 = check_inters(angle2, &inters, &step, 1);
// 	printf("After: inter = %.2f, step = %.2f, result = %d\n", inters, step, result2);
// 	//Result: Flip direction and move downwards (no change to inter).

// 	inters = 0.0;
// 	step = TILE_SIZE;

// 	float angle3 = M_PI / 3; // 60 degrees, points right;
// 	printf("Before: inter = %.2f, step = %.2f\n", inters, step);
// 	int result3 = check_inters(angle3, &inters, &step, 0);
// 	printf("After: inter = %.2f, step = %.2f, result = %d\n", inters, step, result3);
// 	//Result: Move to the next tile right.

// 	inters = 0.0;
// 	step = TILE_SIZE;

// 	float angle4 = 4 * M_PI / 3; // 240 degrees, points left;
// 	printf("Before: inter = %.2f, step = %.2f\n", inters, step);
// 	int result4 = check_inters(angle4, &inters, &step, 0);
// 	printf("After: inter = %.2f, step = %.2f, result = %d\n", inters, step, result4);
// 	//Result: Flip direction and move left (no change to inter).
// }

// int main()
// {
//     char *map[] = {
//         "111111",
//         "100001",
//         "100001",
//         "100001",
//         "111111"};

//     // float x = 150;
//     // float y = 80;

//     float x = 50;
//     float y = 50;
//     t_mapdata mapdata;
//     t_game    game;

//     mapdata.map2d = map;
//     mapdata.map_h = 5;
//     mapdata.map_w = 6;

//     game.mapdata = &mapdata;

//     if(hit_the_wall(x, y, &game))
//     printf("the wall was hit at pos: %f, %f\n", x, y);
//     else
//     printf("the wall was not hit\n");
// }
