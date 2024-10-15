/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:19:13 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 16:39:32 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_stack	make_stack(int capacity)
{
	t_stack	stack;

	stack.cap = capacity;
	stack.len = 0;
	stack.data = ft_calloc(capacity, sizeof(t_coord));
	return (stack);
}

void	push(t_stack *stack, t_coord coord)
{
	t_coord	*new_data;

	if (stack->len >= stack->cap)
	{
		new_data = ft_calloc(stack->cap * 2, sizeof(t_coord));
		ft_memcpy(new_data, stack->data, stack->cap * sizeof(t_coord));
		stack->cap *= 2;
	}
	stack->data[stack->len] = coord;
	stack->len++;
}

int	pop(t_stack *stack, t_coord *dst)
{
	if (stack->len == 0)
	{
		return (0);
	}
	stack->len--;
	*dst = stack->data[stack->len];
	return (1);
}

t_coord	new_coord(int x, int y)
{
	t_coord	c;

	c.x = x;
	c.y = y;
	return (c);
}

int	has_holes(t_mapdata map, t_player player)
{
	t_stack stack;
	int found_holes;
	char *visited;
    t_coord curr;
    t_coord neighbours[4];
    t_coord neighbour;

	stack = make_stack(1024);
	found_holes = 0;
	visited = calloc(map.map_h * map.map_w, sizeof(char));
	push(&stack, new_coord(player.player_x, player.player_y));
	while (stack.len > 0)
	{
		pop(&stack, &curr);
		neighbours[0] = new_coord(curr.x - 1, curr.y);
		neighbours[1] = new_coord(curr.x + 1, curr.y);
		neighbours[2] = new_coord(curr.x, curr.y - 1);
		neighbours[3] = new_coord(curr.x, curr.y + 1);

		for (int i = 0; i < 4; i++)
		{
			t_coord neighbour = neighbours[i];
			if (neighbour.x < 0 || neighbour.y < 0 || neighbour.x >= map.map_w
				|| neighbour.y >= map.map_h)
			{
				printf("found hole at x=%d y=%d\n", neighbour.x, neighbour.y);
				found_holes = 1;
				break ;
			}
			if (map.map2d[neighbour.y][neighbour.x] == '0'
				&& !visited[neighbour.y * map.map_w + neighbour.x])
			{
				visited[neighbour.y * map.map_w + neighbour.x] = 1;
				push(&stack, neighbour);
			}
		}
		if (found_holes)
			break ;
	}
	free(stack.data);
	free(visited);

	return (found_holes);
}
