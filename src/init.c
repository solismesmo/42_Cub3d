/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:18:35 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 20:25:40 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_map(t_game *game)
{
	char	*tmp;
	char	*map_full;

	map_full = NULL;
	game->map.line = get_next_line(game->fd);
	while (game->map.line != NULL)
		ft_parsing_file(game);
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

void	ft_init_moves(t_game *game)
{
	game->map.row_move[0] = -1;
	game->map.row_move[1] = 1;
	game->map.row_move[2] = 0;
	game->map.row_move[3] = 0;
	game->map.col_move[0] = 0;
	game->map.col_move[1] = 0;
	game->map.col_move[2] = -1;
	game->map.col_move[3] = 1;
	game->moves = 0;
	game->map.check_coins = 0;
	game->map.matrix_fill = NULL;
}

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

void	ft_init_map_matrix(t_game *game)
{
	ft_map_lego(game);
	ft_char_check(game);
	ft_check_closed(game);
}

void	ft_init_mlx(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WINDOW_WIDTH, \
	WINDOW_HEIGHT, "Cube 3D", true);
	if (!game->mlx)
	{
		ft_error("Erro na mlx. \n", game);
		exit(1);
	}
}
