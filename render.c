/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:57:33 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 15:18:19 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_image	*get_texture(t_game *game, t_direction face)
{
	if (face == DIRECTION_EAST)
		return (&game->mapdata.east_wall);
	if (face == DIRECTION_WEST)
		return (&game->mapdata.west_wall);
	if (face == DIRECTION_SOUTH)
		return (&game->mapdata.south_wall);
	return (&game->mapdata.north_wall);
}

int	get_colour(t_direction face)
{
	if (face == DIRECTION_EAST)
		return (PSYCHEDELIC_PINK);
	if (face == DIRECTION_WEST)
		return (PURPLE);
	if (face == DIRECTION_SOUTH)
		return (PSYCHEDELIC_LIME);
	return (BLUE);
}

unsigned int	my_mlx_pixel_get(t_image img, int x, int y)
{
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;

	addr = mlx_get_data_addr(img.img, &bits_per_pixel, &line_size, &endian);
	return (*(unsigned int *)(&addr[y * line_size + x * bits_per_pixel / 8]));
}

void	draw_wall(t_game *game, int ray_counter, t_pix pix,
		t_hit hit)
{
	double	x_o;
	double	y_o;
	t_image	*texture;
	double	factor;
	double	wall_h;

	texture = get_texture(game, hit.face);
	wall_h = (1. / hit.distance) * ((SCREEN_WIDTH / 2)
			/ tan(game->player.fov_radians / 2));
	factor = (double)texture->img_h / wall_h;
	x_o = hit.local_x * texture->img_w;
	y_o = (pix.t_pix - (SCREEN_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (pix.t_pix < pix.b_pix)
	{
		my_mlx_pixel_put(&game->img, ray_counter, (int)pix.t_pix,
			my_mlx_pixel_get(*texture, x_o, y_o));
		y_o += factor;
		pix.t_pix++;
	}
}

void	render_wall(t_game *game, int ray_counter, t_hit hit)
{
	double	wall_h;
	t_pix	pix;

	hit.distance *= cos(nor_angle(hit.angle - game->player.angle));
	wall_h = (1. / hit.distance) * ((SCREEN_WIDTH / 2)
			/ tan(game->player.fov_radians / 2));
	pix.b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2);
	pix.t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2);
	if (pix.b_pix > SCREEN_HEIGHT)
		if (pix.t_pix < 0)
			pix.t_pix = 0;
	draw_floor_ceiling(game, ray_counter, pix);
	draw_wall(game, ray_counter, pix, hit);
}
