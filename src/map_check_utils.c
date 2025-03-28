/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:44:25 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/03/27 20:40:40 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			{
				printf("Char: %c\n", game->map.matrix[i][j]);
				ft_error("Forbidden char on the map\n", game);
			}
			j++;
		}
		i++;
	}
	game->map.rows = i;
}

void	ft_map_condition(t_game *game)
{
	if (game->map.player != 1)
		ft_error("Have zero or more then one player\n", game);
	return ;
}

void	ft_map_lego(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.lines)
	{
		j = 0;
		if (game->map.check_inputs != 6)
			ft_error("Error: Missing texture or color\n", game);
		while (game->map.matrix[i][j])
		{
			if (game->map.matrix[i][j] == 'P' || game->map.matrix[i][j] == 'N'\
				|| game->map.matrix[i][j] == 'S' || \
				game->map.matrix[i][j] == 'W'\
				|| game->map.matrix[i][j] == 'E')
			{
				game->map.player++;
				game->map.p_row = i;
				game->map.p_col = j;
			}
			j++;
		}
		i++;
	}
	ft_map_condition(game);
}
