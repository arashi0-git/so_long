/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:20:09 by aryamamo          #+#    #+#             */
/*   Updated: 2024/11/17 12:31:37 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	ft_printstr(char *str)
{
	int	len;

	if (str == NULL)
		return (ft_printstr("(null)"));
	len = 0;
	while (str[len])
	{
		if (ft_putchar(str[len]) < 0)
			return (-1);
		len++;
	}
	return (len);
}

int	ft_printnbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	if (num == NULL)
		return (-1);
	len = ft_printstr(num);
	free(num);
	return (len);
}

int	ft_printpercent(void)
{
	return (ft_putchar('%'));
}
