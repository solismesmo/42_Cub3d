/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:44:25 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/01/15 21:57:32 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mark_visited(t_game	*game, int row, int col)
{
	if (game->map.matrix_fill[row][col] == 'E')
		return ;
	game->map.matrix_fill[row][col] = 'x';
	if (game->map.matrix[row][col] == 'C')
		game->map.check_coins++;
}

int	ft_dfs(t_game *game, int row, int col)
{
	int	next_row;
	int	next_col;
	int	i;

	if (game->map.matrix[row][col] == 'E' \
	&& game->map.check_coins == game->map.coin)
		return (1);
	ft_mark_visited(game, row, col);
	i = 0;
	while (i < 4)
	{
		next_row = row + game->map.row_move[i];
		next_col = col + game->map.col_move[i];
		if (next_row >= 0 && next_row < game->map.rows \
		&& next_col >= 0 && next_col < game->map.columns && \
		game->map.matrix[next_row][next_col] != '1' && \
		game->map.matrix_fill[next_row][next_col] != 'x')
		{
			if (ft_dfs(game, next_row, next_col))
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_check_path(t_game *game)
{
	if (ft_dfs(game, game->map.p_row, game->map.p_col))
		return ;
	else
		ft_error("No valid Path on map", game);
}

int	ft_char_allowed(char c)
{
	if (c == 'E' || c == 'C' || c == 'P' || c == '1' || c == '0')
		return (1);
	else
		return (0);
}

void	ft_char_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.lines)
	{
		j = 0;
		while (game->map.matrix[i][j])
		{
			if (!ft_char_allowed(game->map.matrix[i][j]))
				ft_error("Forbidden char on the map\n", game);
			j++;
		}
		i++;
	}
	game->map.rows = i;
	game->map.matrix_fill = ft_split(game->map.map_full, '\n');
	ft_last_line(game->map.matrix, game);
}
