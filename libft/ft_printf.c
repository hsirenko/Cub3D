/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:06:59 by kkaremin          #+#    #+#             */
/*   Updated: 2024/10/07 18:11:13 by kseniakarem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contains(char needle, char *haystack)
{
	while (*haystack)
	{
		if (*haystack == needle)
		{
			return (1);
		}
		haystack++;
	}
	return (0);
}

int	try_print_percent(char next)
{
	if (next == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (0);
}

int	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int			printed;
	va_list		args;
	const char	*i;

	i = format;
	printed = 0;
	va_start(args, format);
	while (i && *i)
	{
		if (*i != '%')
		{
			printed += ft_putchar(*i);
			i++;
			continue ;
		}
		printed += try_print_percent(*(i + 1));
		if (contains(*(i + 1), "ciduxX"))
			printed += print_4bytes(*(i + 1), va_arg(args, int));
		if (contains(*(i + 1), "sp"))
			printed += print_8bytes(*(i + 1), va_arg(args, long long));
		if (*(i++ + 1) != '\0')
			i += 1;
	}
	va_end(args);
	return (printed);
}
