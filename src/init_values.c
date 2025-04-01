/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 08:36:33 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 13:39:41 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_moves(t_game *game)
{
	game->map.row_move[0] = -1;
	game->map.row_move[1] = 1;
	game->map.row_move[2] = 0;
	game->map.row_move[3] = 0;
	game->map.row_move[4] = -1;
	game->map.row_move[5] = -1;
	game->map.row_move[6] = 1;
	game->map.row_move[7] = 1;
	game->map.col_move[0] = 0;
	game->map.col_move[1] = 0;
	game->map.col_move[2] = -1;
	game->map.col_move[3] = 1;
	game->map.col_move[4] = -1;
	game->map.col_move[5] = 1;
	game->map.col_move[6] = -1;
	game->map.col_move[7] = 1;
	game->map.matrix_fill = NULL;
	game->img.path_east = NULL;
	game->img.path_north = NULL;
	game->img.path_south = NULL;
	game->img.path_west = NULL;
	game->map.check_inputs = 0;
	game->mlx = NULL;
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
	game->color.r = -1;
	game->color.g = -1;
	game->color.b = -1;
	game->count = 0;
	game->map.lines = 0;
	game->moves = 1;
	game->map.p_col = 0;
	game->map.p_row = 0;
	
	ft_init_moves(game);
	return (game);
}

void	ft_init_mlx(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WINDOW_WIDTH, \
	WINDOW_HEIGHT, "Cube 3D", true);
	if (!game->mlx)
	{
		ft_error("Error: mlx. \n", game);
		exit(1);
	}
}
