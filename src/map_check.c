/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:29:41 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 15:27:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mark_visited(t_game *game, int row, int col)
{
	if (game->map.matrix[row][col] == ' ')
		ft_error("Space inside the map", game);
	game->map.matrix_fill[row][col] = 'x';
}

int ft_dfs_closed(t_game *game, int row, int col)
{
	int i;
	int row_length;

	row_length = strlen(game->map.matrix[row]);
	if ((row == 0 || row == game->map.rows - 1 ||
		 col == 0 || col == row_length - 1) &&
		 game->map.matrix[row][col] != '1')
		ft_error("Missing Walls\n", game);
	ft_mark_visited(game, row, col);
	i = 0;
	while (i < 8)
	{
		int next_row = row + game->map.row_move[i];
		int next_col = col + game->map.col_move[i];
		if (next_row < 0 || next_row >= game->map.rows)
			ft_error("Missing Walls\n", game);
		int next_row_length = strlen(game->map.matrix[next_row]);
		if (next_col < 0 || next_col >= next_row_length)
			ft_error("Missing Walls\n", game);
		if (game->map.matrix[next_row][next_col] != '1' &&
			game->map.matrix_fill[next_row][next_col] != 'x')
		{
			if (!ft_dfs_closed(game, next_row, next_col))
				return (0);
		}
		i++;
	}
	return (1);
}

void ft_check_closed(t_game *game)
{
	if (ft_dfs_closed(game, game->map.p_row, game->map.p_col))
		return;
	else
		ft_error("Missing Walls\n", game);
}

void	print_matrix(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map.matrix[i] != NULL)
	{
		j = 0;
		while (game->map.matrix[i][j] != '\0')
		{
			printf("%c", game->map.matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_fill_matrix(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map.matrix_fill[i] != NULL)
	{
		j = 0;
		while (game->map.matrix_fill[i][j] != '\0')
		{
			printf("%c", game->map.matrix_fill[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}