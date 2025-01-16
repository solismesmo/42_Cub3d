/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_III.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:17:18 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/01/15 22:39:44 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_increment(t_game *game, int i, int j)
{
	game->map.player++;
	game->map.p_row = i;
	game->map.p_col = j;
}

void	ft_map_condition(t_game *game)
{
	// if (game->map.exits != 1)
	// 	ft_error("The map doesn't have exit or have more then one exit\n", game);
	// if (game->map.coin == 0)
	// 	ft_error("The map doesn't have at least one collectable\n", game);
	if (game->map.player != 1)
		ft_error("have zero or more then one player\n", game);
	return ;
}
