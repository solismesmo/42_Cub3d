/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgomes-l <bgomes-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:08:11 by bgomes-l          #+#    #+#             */
/*   Updated: 2023/12/13 10:54:10 by bgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_format(char specifier, va_list ap, const char next)
{
	int	count;

	if (specifier == 'c')
		count = ft_print_char(va_arg (ap, int));
	if (specifier == 's')
		count = ft_print_str(va_arg (ap, char *));
	if (specifier == 'd' || specifier == 'i')
		count = ft_print_digit((long)va_arg (ap, int), 10, DEC_BASE);
	if (specifier == 'u')
		count = ft_print_digit((long)va_arg (ap, unsigned int), 10, DEC_BASE);
	if (specifier == 'x')
		count = ft_print_digit((long)va_arg (ap, unsigned int), 16, HEXA_LOW);
	if (specifier == 'X')
		count = ft_print_digit((long)va_arg (ap, unsigned int), 16, HEXA_UP);
	if (specifier == 'p')
		count = ft_print_pointer((long)va_arg (ap, unsigned long));
	if (specifier == '%')
		count = ft_print_char(37);
	if (specifier == '#')
		count = ft_hashflag((long)va_arg (ap, unsigned int), 16, next);
	if (specifier == ' ')
		count = ft_spaceflag(ap, next);
	if (specifier == '+')
		count = ft_moreflag(va_arg(ap, int));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			count;
	const char	*next;

	va_start(ap, format);
	count = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		next = format + 1;
		if (*format == '%' && (*next == 32 || *next == 43 || *next == 35))
		{
			next = format + 2;
			count += ft_print_format(*(++format), ap, *next);
			++format;
		}
		else if (*format == '%')
			count += ft_print_format(*(++format), ap, *next);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}
