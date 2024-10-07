/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unsint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaremin <kkaremin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:57:50 by kkaremin          #+#    #+#             */
/*   Updated: 2023/06/19 19:56:36 by kkaremin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_unsint(unsigned int uns)
{
	int				counter;
	unsigned int	c;

	counter = 1;
	if (uns >= 10)
	{
		counter += put_unsint(uns / 10);
	}
	c = uns % 10 + '0';
	write(1, &c, 1);
	return (counter);
}
