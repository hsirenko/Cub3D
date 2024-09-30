/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaremin <kkaremin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:16:34 by kkaremin          #+#    #+#             */
/*   Updated: 2023/01/19 15:19:42 by kkaremin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_findsize(const char *s, char c)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		if (*s != c)
		{
			size++;
			while (*s && *s != c)
				s++;
		}
		else
		{
			s++;
		}
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**str;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char *) * (ft_findsize(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			str[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	str[i] = 0;
	return (str);
}
