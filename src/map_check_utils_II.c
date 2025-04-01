/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:48:24 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/04/01 07:41:49 by bruno            ###   ########.fr       */
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
		if (game->map.check_inputs != 6)
			ft_error("Error: Missing texture or color\n", game);
		while (game->map.matrix[i][j])
		{
			if (game->map.matrix[i][j] == 'P' || game->map.matrix[i][j] == 'N' \
			|| game->map.matrix[i][j] == 'S' || game->map.matrix[i][j] == 'W' \
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
