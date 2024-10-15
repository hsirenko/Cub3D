/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:21:27 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 14:22:11 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_byte_n(char *s, int n)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < n)
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		res = res * 10 + (s[i] - '0');
		i++;
	}
	if (res < 0 || res > 255)
		return (-1);
	return (res);
}

int	index_of(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	read_color(char **str, char sep)
{
	int	sep_pos;
	int	res;

	sep_pos = index_of(*str, sep);
	if (sep_pos == -1)
		return (-1);
	res = parse_byte_n(*str, sep_pos);
	if (res == -1)
		return (-1);
	*str += sep_pos + 1;
	return (res);
}

int	read_colors(char **str)
{
	int	red;
	int	green;
	int	blue;

	red = read_color(str, ',');
	green = read_color(str, ',');
	blue = read_color(str, '\n');
	if (red == -1 || blue == -1 || green == -1)
		return (-1);
	return (red << 16 | green << 8 | blue);
}

int	get_colors(t_game *game, char **inp_string)
{
	if ((*inp_string)[0] == '\n')
		*inp_string = trim_str(1, *inp_string);
	if ((*inp_string)[0] == 'F')
	{
		*inp_string = trim_str(2, *inp_string);
		game->color_floor = read_colors(inp_string);
		if (game->color_floor == -1)
			return (0);
	}
	if ((*inp_string)[0] == 'C')
	{
		*inp_string = trim_str(2, *inp_string);
		game->color_ceiling = read_colors(inp_string);
		if (game->color_ceiling == -1)
			return (0);
	}
	return (1);
}
