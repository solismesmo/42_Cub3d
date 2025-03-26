/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:44:25 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/03/26 17:04:54 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_char_allowed(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '1' || c == '0' || c == '\n')
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
	// if (game->map.exits != 1)
	// 	ft_error("The map doesn't have exit or have more then one exit\n", game);
	// if (game->map.coin == 0)
	// 	ft_error("The map doesn't have at least one collectable\n", game);
	if (game->map.player != 1)
		ft_error("Have zero or more then one player\n", game);
	return ;
} 

