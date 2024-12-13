/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:07:49 by aryamamo          #+#    #+#             */
/*   Updated: 2024/11/17 12:25:34 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_formats(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_putchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_length += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_length += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_length += ft_printpercent();
	else
		return (-1);
	return (print_length);
}

static int	ft_check_format(const char *str, va_list args, int *print_length)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			result = ft_formats(args, str[i + 1]);
			if (result < 0)
				return (-1);
			*print_length += result;
			i++;
		}
		else
		{
			result = ft_putchar(str[i]);
			if (result < 0)
				return (-1);
			*print_length += result;
		}
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		print_length;
	int		result;

	result = 0;
	print_length = 0;
	va_start(args, str);
	result = ft_check_format(str, args, &print_length);
	va_end(args);
	if (result < 0)
		return (-1);
	return (print_length);
}
