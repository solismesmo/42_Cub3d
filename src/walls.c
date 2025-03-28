/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:32:45 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 20:39:36 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	t_missing_walls(t_game *game, char *temp, char *line, int len)
{
	if (game->map.lines > 1)
	{
		if (*line != '1' || *temp != '1')
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

void	ft_map_walls(t_game *game)
{
	int		len;
	char	*temp;
	char	*line;

	line = game->map.line;
	game->map.lines++;
	while (*line == ' ')
		line++;
	len = ft_strlen(line);
	temp = line + (len - 2);
	while (*temp == ' ')
	{
		temp--;
		len--;
	}
	ft_missing_walls(game, temp, line, len);
	game->map.columns = ft_strlen(line);
}
