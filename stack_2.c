/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:32:35 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 18:40:12 by hsirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_neighbours_of(t_coord curr, t_coord *neighbours)
{
	neighbours[0] = new_coord(curr.x - 1, curr.y);
	neighbours[1] = new_coord(curr.x + 1, curr.y);
	neighbours[2] = new_coord(curr.x, curr.y - 1);
	neighbours[3] = new_coord(curr.x, curr.y + 1);
}

int	_has_holes(t_mapdata map, t_stack *stack, char *visited)
{
	int		i;
	t_coord	curr;
	t_coord	neighbours[4];
	t_coord	neighbour;

	while (stack->len > 0)
	{
		pop(stack, &curr);
		fill_neighbours_of(curr, neighbours);
		i = -1;
		while (++i < 4)
		{
			neighbour = neighbours[i];
			if (neighbour.x < 0 || neighbour.y < 0 || neighbour.x >= map.map_w
				|| neighbour.y >= map.map_h)
				return (1);
			if (map.map2d[neighbour.y][neighbour.x] != '0'
				|| visited[neighbour.y * map.map_w + neighbour.x])
				continue ;
			visited[neighbour.y * map.map_w + neighbour.x] = 1;
			push(stack, neighbour);
		}
	}
	return (0);
}
