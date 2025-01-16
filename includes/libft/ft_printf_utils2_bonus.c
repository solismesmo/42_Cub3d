/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgomes-l <bgomes-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:57:45 by bgomes-l          #+#    #+#             */
/*   Updated: 2023/12/13 10:53:54 by bgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hashflag(long nbr, int base, char next)
{
	int	cont;

	cont = 0;
	if (nbr == 0)
	{
		cont += ft_print_char('0');
		return (cont);
	}
	if (next == 'x')
	{
		cont += ft_print_str("0x");
		cont += ft_print_digit(nbr, base, HEXA_LOW);
	}
	else if (next == 'X')
	{
		cont += ft_print_str("0X");
		cont += ft_print_digit(nbr, base, HEXA_UP);
	}
	return (cont);
}

int	ft_moreflag(int number)
{
	int	cont;

	cont = 0;
	if (number >= 0)
	{
		cont += ft_print_char('+');
		cont += ft_print_digit(number, 10, DEC_BASE);
	}
	else
		cont += ft_print_digit(number, 10, DEC_BASE);
	return (cont);
}

int	ft_spaceflag(va_list args, char next)
{
	int	cont;
	int	num;

	cont = 0;
	if (next == 'd' || next == 'i')
	{
		num = va_arg(args, int);
		if (num >= 0)
		{
			cont += ft_print_char(' ');
			cont += ft_print_digit(num, 10, DEC_BASE);
		}
		else
			cont += ft_print_digit(num, 10, DEC_BASE);
	}
	if (next == 's')
	{
		cont += ft_print_str(va_arg(args, char *));
	}
	return (cont);
}
