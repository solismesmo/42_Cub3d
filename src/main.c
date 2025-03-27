/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:14:31 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 01:53:33 by bruno            ###   ########.fr       */
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
	game->map.check_inputs = 0;
	ft_init_moves(game);
	return (game);
}

int	ft_is_header_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
	    !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ||
	    !ft_strncmp(line, "F", 1)  || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

void	ft_is_path_null(t_game *game)
{
	if(game->img.path_north != NULL)
	{
		free(game->img.path_north);
		game->img.path_north = NULL;
	}
	if(game->img.path_south != NULL)
	{
		free(game->img.path_south);
		game->img.path_south = NULL;
	}
	if(game->img.path_west != NULL)
	{
		free(game->img.path_west);
		game->img.path_west = NULL;
	}
	if(game->img.path_east != NULL)
	{
		free(game->img.path_east);
		game->img.path_east = NULL;
	}
}

void	ft_parse_texture(char *line, t_game *game)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || ft_strlen(tokens[0]) > 2 || tokens[2])
	{
		ft_free_map(tokens);
		ft_error("Error: Invalid texture path\n", game);
		return ;
	}
	ft_is_path_null(game);
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
	ft_free_map(tokens);
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
		game->ceiling_color = rgba_to_rgba(r, g, b, 255);
	else
		ft_error("Error: Unknown color identifier\n", game);
}

void	ft_msg_color_fmt(char **tokens, t_game *game)
{
	ft_free_map(tokens);
	ft_error("Error: Invalid color format\n", game);
}

int ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' ||
        c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int ft_check_rgb_format(const char *str) 
{
    int i = 0;
    int numCount = 0;
	
    // Pula espaços em branco
    while (str[i] && ft_isspace((unsigned char)str[i]))
        i++;

    while (numCount < 3) {
        // Verifica se há dígito para iniciar o número
        if (!ft_isdigit((unsigned char)str[i]))
            return 0; // Não encontrou dígito onde deveria iniciar um número

        // Avança enquanto estiver lendo dígitos (o número pode ter mais de um dígito)
        while (str[i] && ft_isdigit((unsigned char)str[i]))
            i++;

        numCount++;

        // Pula espaços em branco
        while (str[i] && ft_isspace((unsigned char)str[i]))
            i++;

        // Se ainda não lemos os três números, deve haver uma vírgula
        if (numCount < 3) {
            if (str[i] != ',')
                return 0; // Esperava uma vírgula
            i++; // pula a vírgula

            // Pula espaços após a vírgula
            while (str[i] && ft_isspace((unsigned char)str[i]))
                i++;

            // E espera um dígito logo após a vírgula
            if (!ft_isdigit((unsigned char)str[i]))
                return 0;
        }
    }

    // Pula os espaços que possam sobrar
    while (str[i] && ft_isspace((unsigned char)str[i]))
        i++;

    // Se houver algum caractere além de espaços, formato inválido
    if (str[i] != '\0')
        return 0;

    return 1;
}

void	ft_parse_color(char *line, t_game *game)
{
	char	**tokens;
	char	**rgb_values;
	int		r, g, b;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || !(ft_check_rgb_format(tokens[1])) || ft_strlen(tokens[0]) > 1 || tokens[2])
		ft_msg_color_fmt(tokens, game);
	rgb_values = ft_split(tokens[1], ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
	{
		ft_free_map(rgb_values);
		ft_free_map(tokens);
		ft_error("Error: Invalid RGB values\n", game);
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_map(rgb_values);
		ft_free_map(tokens);
		ft_error("Error: RGB values must be between 0 and 255\n", game);
	}
	ft_convert_rgb(r, g, b, tokens, game); 	// Converter para formato RGB inteiro
	game->map.check_inputs++;
	ft_free_map(rgb_values);
	ft_free_map(tokens);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

// ft_is_space percorre a string apontada por *str e retorna 1 se
// todos os caracteres forem espaços; caso contrário, retorna 0.
int	ft_is_space(char **str)
{
	int i;

	// Verifica se a string ou o ponteiro para string são nulos
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
		else if (ft_strlen(game->map.line) > 1 && (!is_whitespace(*game->map.line)))
		{
			map_full = ft_strdup(game->map.line);
			game->map.lines++;
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
		game->map.lines++;
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
	//print_fill_matrix(game);
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
	if(game->map.check_inputs !=6)
		ft_error("Error: Missing texture or color\n", game);
	ft_init_mlx(game);
	ft_init_game(game);
	mlx_key_hook(game->mlx, &ft_keyhooks, game);
	mlx_loop(game->mlx);
	ft_finish("Thanks for playing", game);
	return (0);
}
