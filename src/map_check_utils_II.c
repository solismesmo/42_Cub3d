/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:48:24 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/01/15 22:39:44 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_lego(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.lines)
	{
		j = 0;
		while (game->map.matrix[i][j])
		{
			if (game->map.matrix[i][j] == 'E')
				game->map.exits++;
			if (game->map.matrix[i][j] == 'C')
				game->map.coin++;
			if (game->map.matrix[i][j] == '1')
				game->map.walls++;
			if (game->map.matrix[i][j] == 'P')
				ft_increment(game, i, j);
			j++;
		}
		i++;
	}
	ft_map_condition(game);
	ft_char_check(game);
	//ft_check_path(game);
}

void	ft_map_walls(t_game *game)
{
	int		len;
	char	*temp;

	game->map.lines++;
	len = ft_strlen(game->map.line);
	temp = game->map.line + (len - 2);
	if (game->map.lines > 1)
	{
		if (*game->map.line != '1' || *temp != '1')
			ft_error("Missing walls\n", game);
	}
	else
	{
		while (len > 1)
		{	
			if (*temp != '1')
				ft_error("Missing walls\n", game);
			else
			{
				len --;
				temp--;
			}
		}
	}
}

void	ft_check_rectangle(t_game *game)
{
	int		count_columns2;
	char	*lastchar;

	if (game->map.lines > 1)
	{
		count_columns2 = ft_strlen(game->map.line);
		lastchar = ft_strchr(game->map.line, '\n');
		if ((game->map.columns != count_columns2) && (lastchar != NULL))
			ft_error("The map is not rectangular\n", game);
		else if ((game->map.columns != count_columns2) && \
		(lastchar == NULL) && ((game->map.columns - count_columns2) > 1))
			ft_error("The map is not rectangular\n", game);
		else if ((game->map.columns - 1) == game->map.lines)
			ft_error("The map is shaped like a square, not a rectangle", game);
	}
	else
		game->map.columns = ft_strlen(game->map.line);
}

void	ft_last_line(char **matrix, t_game	*game)
{
	int	i;

	i = 0;
	while (matrix[game->map.rows - 1][i])
	{
		if (matrix[game->map.rows - 1][i] != '1')
			ft_error("Missing walls\n", game);
		i++;
	}
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
