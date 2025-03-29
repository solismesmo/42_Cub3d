/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:30:08 by livieira          #+#    #+#             */
/*   Updated: 2025/03/28 23:00:58 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
		c == '\v' || c == '\f' || c == '\r');
}

int	ft_is_space(char **str)
{
	int	i;

	if (!str || !(*str))
		return (0);
	i = 0;
	while ((*str)[i])
	{
		if (!is_whitespace((*str)[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_is_header_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || \
		!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || \
		!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

int	ft_char_allowed(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '1' || \
		c == '0' || c == '\n')
		return (1);
	else
		return (0);
}
