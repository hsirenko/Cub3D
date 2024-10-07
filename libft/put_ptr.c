/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaremin <kkaremin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:12:15 by kkaremin          #+#    #+#             */
/*   Updated: 2023/06/19 19:56:32 by kkaremin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_ptr(unsigned long long ptr, char *alphabet)
{
	size_t	last;
	int		printed;

	if (ptr == 0)
	{
		return (0);
	}
	last = ptr % 16;
	printed = put_ptr(ptr / 16, alphabet);
	ft_putchar_fd(alphabet[last], 1);
	return (printed + 1);
}
