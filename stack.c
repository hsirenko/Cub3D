/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:19:13 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 18:46:12 by hsirenko         ###   ########.fr       */
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
		free(stack->data);
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
	t_stack	stack;
	int		found_holes;
	char	*visited;

	stack = make_stack(1024);
	visited = calloc(map.map_h * map.map_w, sizeof(char));
	push(&stack, new_coord(player.player_x, player.player_y));
	found_holes = _has_holes(map, &stack, visited);
	free(stack.data);
	free(visited);
	return (found_holes);
}
