/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:32:55 by kseniakarem       #+#    #+#             */
/*   Updated: 2024/10/15 17:47:52 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_string	string_with_capacity(int cap)
{
	t_string	s;

	s.cap = cap;
	s.len = 0;
	s.data = ft_calloc(cap + 1, sizeof(char));
	return (s);
}

t_string	string_grow(t_string s, int new_cap)
{
	t_string	res;

	res.cap = new_cap;
	res.data = ft_calloc(new_cap + 1, sizeof(char));
	res.len = s.len;
	ft_memcpy(res.data, s.data, s.len);
	return (res);
}

t_parser_state	new_parser_state(char *src)
{
	t_parser_state	s;

	s.i = 0;
	s.j = 0;
	s.c = 0;
	s.player_count = 0;
	s.src = src;
	s.player = 0;
	return (s);
}

int	has_chars(t_parser_state s)
{
	return (s.src[s.c] != 0);
}

int	parse_newline(t_parser_state *s)
{
	if (s->src[s->c] != '\n')
		return (0);
	s->i++;
	s->j = 0;
	s->c++;
	return (1);
}
