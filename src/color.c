/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 06:18:16 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 19:37:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isrgb(t_game *game, int *i, int *num_count, char *line)
{
	if (!ft_isdigit((unsigned char)game->color.tokens[1][*i]))
	{
		free(line);
		ft_free_map(game->color.tokens);
		ft_error("Error: Invalid color format\n", game);
	}
	while (game->color.tokens[1][*i] && ft_isdigit((unsigned char)game->color.tokens[1][*i]))
		*i += 1;
	*num_count += 1;
	while (game->color.tokens[1][*i] && ft_isspace((unsigned char)game->color.tokens[1][*i]))
		*i += 1;
	if (*num_count < 3)
	{
		if (game->color.tokens[1][*i] != ',')
			return (0);
		*i += 1;
		while (game->color.tokens[1][*i] && ft_isspace((unsigned char)game->color.tokens[1][*i]))
			*i += 1;
		if (!ft_isdigit((unsigned char)game->color.tokens[1][*i]))
			return (0);
	}
	return (1);
}

int	ft_check_rgb_format(t_game *game, char *line)
{
	int	i;
	int	num_count;

	i = 0;
	num_count = 0;
	while (game->color.tokens[1][i] && ft_isspace((unsigned char)game->color.tokens[1][i]))
		i++;
	while (num_count < 3)
	{
		ft_isrgb(game, &i, &num_count, line);
	}
	while (game->color.tokens[1][i] && ft_isspace((unsigned char)game->color.tokens[1][i]))
		i++;
	if (game->color.tokens[1][i] != '\0')
		return (0);
	return (1);
}

uint32_t	rgba_to_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	ft_convert_rgb(t_game *game)
{
	if (ft_strncmp(game->color.tokens[0], "F", 1) == 0)
		game->floor_color = rgba_to_rgba(game->color.r, game->color.g, \
			game->color.b, 255);
	else if (ft_strncmp(game->color.tokens[0], "C", 1) == 0)
		game->ceiling_color = rgba_to_rgba(game->color.r, game->color.g, \
			game->color.b, 255);
	else
		ft_error("Error: Unknown color identifier\n", game);
}

void	ft_msg_color_fmt(t_game *game)
{
	ft_free_map(game->color.tokens);
	ft_error("Error: Invalid color format\n", game);
	return ;
}
