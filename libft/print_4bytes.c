/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_4bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaremin <kkaremin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:02:49 by kkaremin          #+#    #+#             */
/*   Updated: 2023/06/19 19:56:14 by kkaremin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_4bytes(char next, int data)
{
	if (next == 'u')
		return (put_unsint(data));
	if (next == 'd' || next == 'i')
	{
		ft_putnbr_fd(data, 1);
		return (numlen(data));
	}
	if (next == 'c')
	{
		ft_putchar_fd(data, 1);
		return (1);
	}
	if (data == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (next == 'x')
		return (put_ll(*(unsigned int *)(&data), "0123456789abcdef"));
	if (next == 'X')
		return (put_ll(*(unsigned int *)(&data), "0123456789ABCDEF"));
	return (0);
}
