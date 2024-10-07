/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_8bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:04:32 by kkaremin          #+#    #+#             */
/*   Updated: 2023/07/21 15:55:22 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_8bytes(char next, long long data)
{	
	char	*str;

	if (next == 's')
	{
		str = *(char **)(&data);
		if (str != NULL)
		{
			ft_putstr(str);
			return (ft_strlen(str));
		}
		ft_putstr("(null)");
		return (6);
	}
	if (next == 'p')
	{
		if (data == 0)
		{
			ft_putstr_fd("(nil)", 1);
			return (5);
		}
		ft_putstr("0x");
		return (put_ptr(*(unsigned long long *)(&data), "0123456789abcdef")
			+ 2);
	}
	return (0);
}
