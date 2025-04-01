/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:23:11 by livieira          #+#    #+#             */
/*   Updated: 2025/04/01 13:37:29 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calculate_delta_dist(t_game *game)
{
	if (game->camera.ray_dir[0] != 0)
		game->params.delta_distx = fabs(1 / game->camera.ray_dir[0]);
	else
		game->params.delta_distx = INFINITY;
	if (game->camera.ray_dir[1] != 0)
		game->params.delta_disty = fabs(1 / game->camera.ray_dir[1]);
	else
		game->params.delta_disty = INFINITY;
}

void	ft_calculate_perpendicular_dist(t_game *game)
{
	if (game->img.hit_side == 0)
		game->img.perpendicular_dist = fabs((game->params.wall_map_pos[0] - \
			game->player_info.vector_pos[0] + \
			((1 - game->params.step_x) / 2)) / game->camera.ray_dir[0]);
	else
		game->img.perpendicular_dist = fabs((game->params.wall_map_pos[1] - \
		game->player_info.vector_pos[1] + ((1 - game->params.step_y) / 2)) / \
			game->camera.ray_dir[1]);
}

void	ft_calculate_wall_line_height(t_game *game)
{
	double	wall_line_height;

	wall_line_height = (WINDOW_HEIGHT / game->img.perpendicular_dist);
	game->img.wall_line_start = WINDOW_HEIGHT / 2 - wall_line_height / 2;
	game->img.wall_line_end = WINDOW_HEIGHT / 2 + wall_line_height / 2;
}
