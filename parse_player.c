/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:24:47 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 14:26:00 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_height(char *inp_string)
{
	int	h;

	h = 0;
	while (*inp_string)
	{
		if (*inp_string == '\n')
			h++;
		inp_string++;
	}
	return (h + 1);
}

int	get_map_width(char *inp_string)
{
	int	max_len;
	int	len;

	max_len = 0;
	while (*inp_string)
	{
		len = 0;
		while ((*inp_string != '\n') && (*inp_string))
		{
			len++;
			inp_string++;
		}
		if (max_len < len)
			max_len = len;
		if (*inp_string)
			inp_string++;
	}
	return (max_len);
}

int	check(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	find_angle_view(t_game *game, const char c)
{
	if (c == 'E')
		game->player.angle = 0.0f * M_PI;
	else if (c == 'N')
		game->player.angle = 0.5f * M_PI;
	else if (c == 'W')
		game->player.angle = 1.0f * M_PI;
	else if (c == 'S')
		game->player.angle = -0.5f * M_PI;
}

int	check_gamer(char gamer, int gamer_count)
{
	if (gamer_count != 1)
	{
		panic("insufficient amount of gamers");
		return (0);
	}
	if (!check(gamer, "NSWE"))
	{
		panic("insuffifient gamer");
		return (0);
	}
	return (1);
}
