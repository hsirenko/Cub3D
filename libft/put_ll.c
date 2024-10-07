/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaremin <kkaremin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:57:11 by kkaremin          #+#    #+#             */
/*   Updated: 2023/06/19 19:56:27 by kkaremin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_ll(long long n, char *alphabet)
{
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		return (1 + put_ptr(-n, alphabet));
	}
	return (put_ptr(n, alphabet));
}
