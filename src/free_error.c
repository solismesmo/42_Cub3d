/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:52:24 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/01/15 22:08:07 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error_message(char *message)
{
	ft_putstr_fd(message, STDOUT_FILENO);
	exit(1);
}

void	ft_error(char *message, t_game *game)
{
	ft_putstr_fd(message, STDOUT_FILENO);
	if (game->map.line != NULL)
		free(game->map.line);
	if (game->map.map_full != NULL)
		free(game->map.map_full);
	if (game->map.matrix != NULL)
		ft_free_map(game->map.matrix);
	if (game->map.matrix_fill != NULL)
		ft_free_map(game->map.matrix_fill);
	free(game);
	exit(1);
}

void	ft_finish(char *message, t_game *game)
{
	ft_putstr_fd(message, STDOUT_FILENO);
	if (game->map.line != NULL)
		free(game->map.line);
	if (game->map.map_full != NULL)
		free(game->map.map_full);
	if (game->map.matrix != NULL)
		ft_free_map(game->map.matrix);
	if (game->map.matrix_fill != NULL)
		ft_free_map(game->map.matrix_fill);
	if (game->mlx != NULL)
		mlx_terminate(game->mlx);
	free(game);
	exit(0);
}

void	ft_free_map(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
	{
		free(matriz[i]);
		i++;
	}
	free(matriz);
}
