/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:53:44 by helensirenk       #+#    #+#             */
/*   Updated: 2024/09/25 19:27:56 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

float	normalz_angle(float angle)
{
	if (angle < 0)
	{
		angle += (M_PI * 2);
	}
	if (angle > (2 * M_PI))
	{
		angle -= (M_PI * 2);
	}
	return (angle);
}

void	ft_exit(t_game *game)
{
	//mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_display(game->mlx);
	free(game->player);
	free(game->ray);
	mlx_destroy_window(game->mlx, game->win);
	printf("Game is closed\n");
	exit(0);
}