/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:19:23 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 14:19:58 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	find_prefix(char *prefix, char *string)
{
	while (*prefix)
	{
		if (*prefix == *string)
		{
			prefix++;
			string++;
		}
		else
			return (0);
	}
	return (1);
}

char	*trim_str(int len, char *str)
{
	return (&str[len]);
}

int	parse_path(void *mlx, char *direction, char **inp_string, t_image *img)
{
	char	*path;
	char	*end_path;

	if (!find_prefix(direction, *inp_string))
		return (0);
	*inp_string = trim_str(ft_strlen(direction), *inp_string);
	end_path = ft_strchr(*inp_string, '\n');
	path = ft_substr(*inp_string, 0, (end_path - *inp_string));
	*inp_string = trim_str(ft_strlen(path) + 1, *inp_string);
	img->img = mlx_xpm_file_to_image(mlx, path, &img->img_w, &img->img_h);
	if (!img->img)
	{
		return (0);
	}
	return (1);
}

int	get_wall_img(t_game *game, char **inp_string)
{
	int	no;
	int	so;
	int	we;
	int	ea;

	no = parse_path(game->mlx, "NO ", inp_string, &game->mapdata.north_wall);
	if (!no)
		return (0);
	so = parse_path(game->mlx, "SO ", inp_string, &game->mapdata.south_wall);
	if (!so)
		return (0);
	we = parse_path(game->mlx, "WE ", inp_string, &game->mapdata.west_wall);
	if (!we)
		return (0);
	ea = parse_path(game->mlx, "EA ", inp_string, &game->mapdata.east_wall);
	if (!ea)
		return (0);
	return (1);
}
