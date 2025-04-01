/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 05:58:02 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 20:51:17 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_texture(char *line, t_game *game)
{
	game->color.tokens = ft_split(line, ' ');
	if (!game->color.tokens || !game->color.tokens[0] \
		|| !game->color.tokens[1] || \
		ft_strlen(game->color.tokens[0]) > 2 || game->color.tokens[2])
	{
		ft_free_map(game->color.tokens);
		free(line);
		ft_error("Error: Invalid texture path\n", game);
		return ;
	}
	ft_set_texture_aux(game->color.tokens[0], \
		game->color.tokens[1], game, line);
	game->map.check_inputs++;
	ft_free_map(game->color.tokens);
}

void	ft_set_texture_aux(char *id, char *path, t_game *game, char *line)
{
	if (ft_strncmp(id, "NO", 2) == 0 && game->img.path_north == NULL)
		game->img.path_north = ft_strdup(path);
	else if (ft_strncmp(id, "SO", 2) == 0 && game->img.path_south == NULL)
		game->img.path_south = ft_strdup(path);
	else if (ft_strncmp(id, "WE", 2) == 0 && game->img.path_west == NULL)
		game->img.path_west = ft_strdup(path);
	else if (ft_strncmp(id, "EA", 2) == 0 && game->img.path_east == NULL)
		game->img.path_east = ft_strdup(path);
	else
	{
		ft_free_map(game->color.tokens);
		free(line);
		ft_error("Error: Unknown texture identifier\n", game);
	}
}

void	ft_parse_color(char *line, t_game *game)
{
	char	**rgb_values;

	game->color.tokens = ft_split(line, ' ');
	if (!game->color.tokens || !game->color.tokens[0] \
		|| !game->color.tokens[1] || !(ft_check_rgb_format(game, line)) \
		|| ft_strlen(game->color.tokens[0]) > 1 || game->color.tokens[2])
	{
		free(line);
		ft_msg_color_fmt(game);
	}
	rgb_values = ft_split(game->color.tokens[1], ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
		ft_parser_error(rgb_values, game, \
			line, "Error: Invalid RGB values\n");
	game->color.r = ft_atoi(rgb_values[0]);
	game->color.g = ft_atoi(rgb_values[1]);
	game->color.b = ft_atoi(rgb_values[2]);
	if (game->color.r < 0 || game->color.r > 255 || game->color.g < 0 \
		|| game->color.g > 255 || game->color.b < 0 || game->color.b > 255)
		ft_parser_error(rgb_values, game, line, \
			"Error: RGB values must be between 0 and 255\n");
	ft_convert_rgb(game);
	game->map.check_inputs++;
	ft_free_map(rgb_values);
	ft_free_map(game->color.tokens);
}

void	ft_parser_error(char **rgb_values, t_game *game, \
	char *line, char *message)
{
	ft_free_map(rgb_values);
	ft_free_map(game->color.tokens);
	free(line);
	ft_error(message, game);
}
