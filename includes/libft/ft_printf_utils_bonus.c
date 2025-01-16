/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgomes-l <bgomes-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:45:42 by bgomes-l          #+#    #+#             */
/*   Updated: 2023/12/13 10:54:03 by bgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return ((ft_print_str("(null)")));
	while (*str)
	{
		ft_print_char((int)*str);
		++ count;
		++str;
	}
	return (count);
}

int	ft_print_pointer(unsigned long num)
{
	char	*symbols;
	int		count;

	symbols = "0123456789abcdef";
	count = 0;
	if (num == 0)
		return (ft_print_str("(nil)"));
	if (num >= 16)
		count += ft_print_pointer(num / 16);
	else
		count += ft_print_str("0x");
	count += ft_print_char(symbols[num % 16]);
	return (count);
}

int	ft_print_digit(long n, int base, char *symbols)
{
	int		count;
	char	*symbols_f;

	count = 0;
	symbols_f = symbols;
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_digit(-n, base, symbols_f) + 1);
	}
	else if (n < base)
		return (ft_print_char(symbols[n]));
	else
	{
		count = ft_print_digit(n / base, base, symbols_f);
		return (count + ft_print_digit(n % base, base, symbols));
	}
}
