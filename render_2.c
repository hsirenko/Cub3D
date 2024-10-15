/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:02:09 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 15:14:52 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	unsigned int	*pixel_addr;

	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	pixel_addr = (unsigned int *)(img->addr + img->line_length * y + img->bpp
			/ 8 * x);
	*pixel_addr = color;
}

void	draw_floor_ceiling(t_game *game, int ray_counter, t_pix pix)
{
	int	i;

	i = pix.b_pix;
	while (i < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(&game->img, ray_counter, i++, game->color_floor);
	}
	i = 0;
	while (i < pix.t_pix)
		my_mlx_pixel_put(&game->img, ray_counter, i++, game->color_ceiling);
}
