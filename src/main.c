/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:14:31 by livieira          #+#    #+#             */
/*   Updated: 2025/03/25 02:02:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*ft_init_values(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (game == NULL)
		return (NULL);
	game->map.map_full = NULL;
	game->map.matrix = NULL;
	game->map.matrix_fill = NULL;
	game->map.line = NULL;
	game->map.player = 0;
	game->map.columns = 0;
	game->map.rows = 0;
	game->map.coin = 0;
	game->map.exits = 0;
	game->map.floor = 0;
	game->map.walls = 0;
	game->map.enemy = 0;
	game->count = 0;
	game->map.lines = 0;
	game->moves = 1;
	game->map.p_col = 0;
	game->map.p_row = 0;
	ft_init_moves(game);
	return (game);
}

int	ft_is_header_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return (0);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
	    !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ||
	    !ft_strncmp(line, "F", 1)  || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

void	ft_parse_texture(char *line, t_game *game)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
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
	//ft_free_split(tokens);
}

uint32_t rgba_to_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

void	ft_convert_rgb(int r, int g, int b, char **tokens, t_game *game)
{
	if (ft_strncmp(tokens[0], "F", 1) == 0)
		game->floor_color = rgba_to_rgba(r, g, b, 255);
	else if (ft_strncmp(tokens[0], "C", 1) == 0)
	{
		printf("color is %d\n", rgba_to_rgba(r, g, b, 255));
		game->ceiling_color = rgba_to_rgba(r, g, b, 255);
	}
	else
		ft_error("Error: Unknown color identifier\n", game);
}

void	ft_msg_color_fmt(char **tokens, t_game *game)
{
	ft_error("Error: Invalid color format\n", game);
	ft_free_map(tokens);
	return ;
}

void	ft_parse_color(char *line, t_game *game)
{
	char	**tokens;
	char	**rgb_values;
	int		r, g, b;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		ft_msg_color_fmt(tokens, game);
	rgb_values = ft_split(tokens[1], ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
	{
		ft_error("Error: Invalid RGB values\n", game);
		//ft_free_split(rgb_values);
		//ft_free_split(tokens);
		return ;
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_error("Error: RGB values must be between 0 and 255\n", game);
	ft_convert_rgb(r, g, b, tokens, game); 	// Converter para formato RGB inteiro
	//ft_free_split(rgb_values);
	//ft_free_split(tokens);
}


void	ft_init_map(t_game *game)
{
	//char	*line;
	char	*tmp;
	char	*map_full;

	map_full = NULL;
	game->map.line = get_next_line(game->fd);
	while (game->map.line != NULL)
	{
		if (ft_is_header_line(game->map.line))
		{
			if (game->map.line[0] == 'N' || game->map.line[0] == 'S' ||
				game->map.line[0] == 'W' || game->map.line[0] == 'E')
				ft_parse_texture(game->map.line, game);
			else if (game->map.line[0] == 'F' || game->map.line[0] == 'C')
				ft_parse_color(game->map.line, game);
			free(game->map.line);
		}
		else if (ft_strlen(game->map.line) > 1)
		{
			map_full = ft_strdup(game->map.line);
			ft_map_walls(game);
			free(game->map.line);
			break ;
		}
		else
		{
			free(game->map.line);
		}
		game->map.line = get_next_line(game->fd);
	}
	game->map.line = get_next_line(game->fd);
	while (game->map.line != NULL)
	{
		ft_map_walls(game);
		tmp = map_full;
		map_full = ft_strjoin(map_full, game->map.line);
		free(tmp);
		free(game->map.line);
		game->map.line = get_next_line(game->fd);
	}
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

void	ft_init_mlx(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init( WINDOW_WIDTH, \
	WINDOW_HEIGHT, "Cube 3D", true);
	if (!game->mlx)
	{
		ft_error("Erro na mlx. \n", game);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	ft_check_args(argc, argv);
	game = ft_init_values();
	game->map_name = argv[1];
	ft_map_open(game);
	ft_init_map(game);
	ft_init_mlx(game);
	ft_init_game(game);
	mlx_key_hook(game->mlx, &ft_keyhooks, game);
	mlx_loop(game->mlx);
	ft_finish("Thanks for playing", game);
	return (0);
}
