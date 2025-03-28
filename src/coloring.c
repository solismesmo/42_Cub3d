/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:26:24 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 21:18:31 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isrgb(const char *str, int i)
{
	if (!ft_isdigit((unsigned char)str[i]))
		return (0);
	while (str[i] && ft_isdigit((unsigned char)str[i]))
		i++;
	num_count++;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	if (num_count < 3)
	{
		if (str[i] != ',')
			return (0);
		i++;
		while (str[i] && ft_isspace((unsigned char)str[i]))
			i++;
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
	}
}

int	ft_check_rgb_format(const char *str)
{
	int	i;
	int	num_count;

	i = 0;
	num_count = 0;
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	while (num_count < 3)
	{
		ft_isrgb(str, i);
	}
	while (str[i] && ft_isspace((unsigned char)str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

uint32_t	rgba_to_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	ft_convert_rgb(int r, int g, int b, char **tokens, t_game *game)
{
	if (ft_strncmp(tokens[0], "F", 1) == 0)
		game->floor_color = rgba_to_rgba(r, g, b, 255);
	else if (ft_strncmp(tokens[0], "C", 1) == 0)
		game->ceiling_color = rgba_to_rgba(r, g, b, 255);
	else
		ft_error("Error: Unknown color identifier\n", game);
}

void	ft_msg_color_fmt(char **tokens, t_game *game)
{
	ft_error("Error: Invalid color format\n", game);
	ft_free_map(tokens);
	return ;
}
