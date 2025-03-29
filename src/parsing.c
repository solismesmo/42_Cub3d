/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:23:09 by livieira          #+#    #+#             */
/*   Updated: 2025/03/28 23:07:47 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parsing_file(t_game *game)
{
	if (ft_is_header_line(game->map.line))
	{
		if (game->map.line[0] == 'N' || game->map.line[0] == 'S' || \
			game->map.line[0] == 'W' || game->map.line[0] == 'E')
			ft_parse_texture(game->map.line, game);
		else if (game->map.line[0] == 'F' || game->map.line[0] == 'C')
			ft_parse_color(game->map.line, game);
		free(game->map.line);
	}
	else if (ft_strlen(game->map.line) > 1 && \
	(!is_whitespace(*game->map.line)))
	{
		game->map.lines++;
		free(game->map.line);
	}
	else
		free(game->map.line);
	game->map.line = get_next_line(game->fd);
}

void	ft_parse_texture(char *line, t_game *game)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || \
		ft_strlen(tokens[0]) > 2 || tokens[2])
	{
		ft_error("Error: Invalid texture path\n", game);
		return ;
	}
	if (ft_strncmp(tokens[0], "NO", 2) == 0)
		game->img.path_north = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "SO", 2) == 0)
		game->img.path_south = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "WE", 2) == 0)
		game->img.path_west = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "EA", 2) == 0)
		game->img.path_east = ft_strdup(tokens[1]);
	else
		ft_error("Error: Unknown texture identifier\n", game);
	game->map.check_inputs++;
}

void	ft_parse_color(char *line, t_game *game)
{
	char	**tokens;
	char	**rgb_values;
	t_rgb	color;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || \
		!(ft_check_rgb_format(tokens[1])) || \
		ft_strlen(tokens[0]) > 1 || tokens[2])
		ft_msg_color_fmt(tokens, game);
	rgb_values = ft_split(tokens[1], ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
	{
		ft_error("Error: Invalid RGB values\n", game);
		return ;
	}
	color.r = ft_atoi(rgb_values[0]);
	color.g = ft_atoi(rgb_values[1]);
	color.b = ft_atoi(rgb_values[2]);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || \
		color.b < 0 || color.b > 255)
		ft_error("Error: RGB values must be between 0 and 255\n", game);
	ft_convert_rgb(color, tokens, game);
	game->map.check_inputs++;
}
