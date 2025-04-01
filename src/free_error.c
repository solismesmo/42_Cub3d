/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:52:24 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/04/01 18:36:01 by bruno            ###   ########.fr       */
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
	if (game)
	{
		if (game->map.line)
			free(game->map.line);
		if (game->map.map_full)
			free(game->map.map_full);
		if (game->map.matrix)
			ft_free_map(game->map.matrix);
		if (game->map.matrix_fill)
			ft_free_map(game->map.matrix_fill);
		if (game->img.path_east)
			free(game->img.path_east);
		if (game->img.path_north)
			free(game->img.path_north);
		if (game->img.path_south)
			free(game->img.path_south);
		if (game->img.path_west)
			free(game->img.path_west);
		if (game->mlx)
			mlx_terminate(game->mlx);
		// if (game->color.tokens != NULL)
		// 	ft_free_map(game->color.tokens);
		free(game);
	}
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
	if (game->img.path_east != NULL)
		free(game->img.path_east);
	if (game->img.path_north != NULL)
		free(game->img.path_north);
	if (game->img.path_south != NULL)
		free(game->img.path_south);
	if (game->img.path_west != NULL)
		free(game->img.path_west);
	free(game);
	exit(0);
}

void	ft_free_map(char **matriz)
{
	int	i;

	i = 0;
	if (*matriz)
	{
		while (matriz[i])
		{
			free(matriz[i]);
			i++;
		}
		free(matriz);
		matriz = NULL;
	}
}