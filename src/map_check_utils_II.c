/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:48:24 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/03/27 20:38:02 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_superior_line(t_game *game, int j)
{
	if (game->map.matrix[0][j] != '1' && game->map.matrix[0][j] != ' ')
	{
		printf("Error: open map in superior line.\n");
		exit(1);
	}
}

void	ft_inferior_line(t_game game, int j)
{
	if (game->map.matrix[game->map.lines - 1][j] != '1' && \
		game->map.matrix[game->map.lines - 1][j] != ' ')
	{
		printf("Error: open map inferior line.\n");
		exit(1);
	}
}

void	ft_map_cols(t_game *game, int i, int j)
{
	if (game->map.matrix[i][0] != '1' && game->map.matrix[i][0] != ' ')
	{
		printf("Error: open map col L.\n");
		exit(1);
	}
	if (game->map.matrix[i][game->map.columns - 1] != '1' && \
		game->map.matrix[i][game->map.columns - 1] != ' ')
	{
		printf("Error: open map col R.\n");
		exit(1);
	}
}

void	ft_check_walls(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (game->map.matrix[0][j])
	{
		ft_superior_line(game, j);
		j++;
	}
	j = 0;
	while (game->map.matrix[game->map.lines - 1][j])
	{
		ft_inferior_line(game, j);
		j++;
	}
	i = 0;
	while (i < game->map.lines)
	{
		ft_map_cols(game, i, j);
		i++;
	}
}
