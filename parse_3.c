/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:28:04 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 16:28:16 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	current_char(t_parser_state s)
{
	return (s.src[s.c]);
}

int	parse_player(t_parser_state *s)
{
	if (check(current_char(*s), " 01"))
		return (0);
	s->player_count++;
	s->player = current_char(*s);
	return (1);
}

void	parse_wall_or_player(t_parser_state *s, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (current_char(*s) == '1')
		game->mapdata.map2d[i][j] = '1';
	else
		game->mapdata.map2d[i][j] = '0';
	if (parse_player(s))
	{
		game->player.player_x = j + 0.5;
		game->player.player_y = i + 0.5;
	}
	advance(s);
}
