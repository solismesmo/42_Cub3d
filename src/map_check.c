/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:29:41 by bruno             #+#    #+#             */
/*   Updated: 2025/03/26 18:57:35 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mark_visited(t_game *game, int row, int col)
{
	game->map.matrix_fill[row][col] = 'x';
}

int	ft_dfs_done(int next_row, int col, int col_move, t_game *game)
{
	int	next_col;
	int	next_row_length;

	next_col = col + col_move[i];
	if (next_row < 0 || next_row >= game->map.rows)
	{
		printf("Error: open map on line %d\n", next_row);
		return (0);
	}
	next_row_length = strlen(game->map.matrix[next_row]);
	if (next_col < 0 || next_col >= next_row_length)
	{
		printf("Error: map open at position [%d][%d] (line length: %d)\n", \
			next_row, next_col, next_row_length);
		return (0);
	}
	if (game->map.matrix[next_row][next_col] != '1' &&
		game->map.matrix_fill[next_row][next_col] != 'x')
	{
		if (!ft_dfs_closed(game, next_row, next_col))
			return (0);
	}
}

int	ft_dfs_closed(t_game *game, int row, int col)
{
	int	i;
	int	row_length;
	int	row_move;
	int	col_move;
	int	next_row;

	row_length = strlen(game->map.matrix[row]);
	row_move[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
	col_move[8] = {0, 0, -1, 1, -1, 1, -1, 1};
	if ((row == 0 || row == game->map.rows - 1 || \
		col == 0 || col == row_length - 1) && \
		game->map.matrix[row][col] != '1')
	{
		printf("Error: map open at position [%d][%d]\n", row, col);
		return (0);
	}
	ft_mark_visited(game, row, col);
	next_row = row + row_move;
	i = 0;
	while (i < 8)
	{
		ft_dfs_done(next_row, col, col_move, game);
		i++;
	}
	return (1);
}

void	ft_check_closed(t_game *game)
{
	if (ft_dfs_closed(game, game->map.p_row, game->map.p_col))
		return ;
	else
		ft_error("The map is not closed by walls", game);
}
