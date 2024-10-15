/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:15:51 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 16:16:49 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*read_file(int fd)
{
	int			bytes_read;
	t_string	str;

	str = string_with_capacity(1024);
	while (1)
	{
		bytes_read = read(fd, &str.data[str.len], str.cap - str.len);
		if (bytes_read < 0)
		{
			free(str.data);
			panic("read call failed");
			return (NULL);
		}
		if (!bytes_read)
		{
			return (str.data);
		}
		str.len += bytes_read;
		if (str.len == str.cap)
			str = string_grow(str, str.cap * 2);
	}
	panic("unreachable file");
}

int	fill_map(t_game *game, char *src)
{
	t_parser_state	s;

	s = new_parser_state(src);
	while (has_chars(s))
	{
		if (parse_newline(&s))
			continue ;
		parse_wall_or_player(&s, game);
	}
	if (!check_gamer(s.player, s.player_count))
		return (0);
	game->player.start_orient = s.player;
	find_angle_view(game, s.player);
	return (1);
}

int	get_map(t_game *game, char **inp_string)
{
	int	i;

	if ((*inp_string)[0] == '\n')
		*inp_string = trim_str(1, *inp_string);
	game->mapdata.map_h = get_map_height(*inp_string);
	game->mapdata.map_w = get_map_width(*inp_string);
	game->mapdata.map2d = ft_calloc(game->mapdata.map_h, sizeof(char *));
	i = 0;
	while (i < game->mapdata.map_h)
	{
		game->mapdata.map2d[i] = ft_calloc(game->mapdata.map_w, sizeof(char));
		ft_memset(game->mapdata.map2d[i], '0', game->mapdata.map_w);
		i++;
	}
	fill_map(game, *inp_string);
	return (1);
}

int	parse(t_game *game, int fd)
{
	char	*inp_string;

	inp_string = read_file(fd);
	if (!get_wall_img(game, &inp_string))
	{
		panic("could not parse image paths");
		return (0);
	}
	if (!(get_colors(game, &inp_string) == 1))
	{
		panic("could not parse floor and ceiling colors");
		return (0);
	}
	if (!(get_map(game, &inp_string)))
	{
		panic("could not get map or it's invalid");
		return (0);
	}
	return (1);
}

void	init_struct_game(t_game *game, char *file_name)
{
	int	status;
	int	fd;

	(void)game;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		panic("could not open file");
	}
	status = parse(game, fd);
	if (status == 0)
	{
		panic("failed to parse map");
	}
	if (has_holes(game->mapdata, game->player))
	{
		panic("map has holes");
	}
}
