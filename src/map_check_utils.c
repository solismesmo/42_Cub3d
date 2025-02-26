/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:44:25 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/02/26 19:42:09 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_char_allowed(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '1' || c == '0')
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
	printf("Chamando ft_split com map_full:\n%s\n", game->map.map_full);
	game->map.matrix_fill = ft_split(game->map.map_full, '\n');
	ft_last_line(game->map.matrix, game);
}
