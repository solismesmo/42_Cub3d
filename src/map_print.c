/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:55:51 by livieira          #+#    #+#             */
/*   Updated: 2025/03/26 18:56:07 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_fill_matrix(t_game *game)
{
	int	i;
	int	j;

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

void	print_matrix(t_game *game)
{
	int	i;
	int	j;

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
