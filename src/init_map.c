/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:18:35 by livieira          #+#    #+#             */
/*   Updated: 2025/03/30 08:37:58 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_parse_header_line(char *line, t_game *game)
{
	if (line[0] == 'N' || line[0] == 'S' || \
		line[0] == 'W' || line[0] == 'E')
		ft_parse_texture(line, game);
	else if (line[0] == 'F' || line[0] == 'C')
		ft_parse_color(line, game);
}

static char	*ft_process_header(t_game *game)
{
	char	*line;
	char	*map_full;

	map_full = NULL;
	line = get_next_line(game->fd);
	while (line)
	{
		if (ft_is_header_line(line))
		{
			ft_parse_header_line(line, game);
			free(line);
		}
		else if (ft_strlen(line) > 1 && !is_whitespace(*line))
		{
			map_full = ft_strdup(line);
			game->map.lines++;
			free(line);
			break ;
		}
		else
			free(line);
		line = get_next_line(game->fd);
	}
	return (map_full);
}

static char	*ft_process_map(t_game *game, char *map_full)
{
	char	*line;
	char	*tmp;

	line = get_next_line(game->fd);
	while (line)
	{
		game->map.lines++;
		tmp = map_full;
		map_full = ft_strjoin(map_full, line);
		free(tmp);
		free(line);
		line = get_next_line(game->fd);
	}
	return (map_full);
}

void	ft_init_map(t_game *game)
{
	char	*map_full;

	map_full = ft_process_header(game);
	map_full = ft_process_map(game, map_full);
	if (!map_full)
		ft_error("Error, empty map!\n", game);
	game->map.map_full = map_full;
	game->map.matrix = ft_split(game->map.map_full, '\n');
	game->map.matrix_fill = ft_split(game->map.map_full, '\n');
	ft_init_map_matrix(game);
}

void	ft_init_map_matrix(t_game *game)
{
	ft_map_lego(game);
	ft_char_check(game);
	ft_check_closed(game);
}
