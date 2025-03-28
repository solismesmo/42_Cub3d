/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:23:11 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 21:35:01 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_calculate_delta_dist(t_game *game, t_dda_params *params)
{
	if (game->camera.ray_dir[0] != 0)
		params->delta_distx = fabs(1 / game->camera.ray_dir[0]);
	else
		params->delta_distx = INFINITY;
	if (game->camera.ray_dir[1] != 0)
		params->delta_disty = fabs(1 / game->camera.ray_dir[1]);
	else
		params->delta_disty = INFINITY;
}

static void	ft_calculate_perpendicular_dist(t_game *game, t_dda_params *params)
{
	if (game->img.hit_side == 0)
		game->img.perpendicular_dist = fabs((params->wall_map_pos[0] - \
			game->player_info.vector_pos[0] + ((1 - params->step_x) / 2)) / \
			game->camera.ray_dir[0]);
	else
		game->img.perpendicular_dist = fabs((params->wall_map_pos[1] - \
		game->player_info.vector_pos[1] + ((1 - params->step_y) / 2)) / \
			game->camera.ray_dir[1]);
}

static void	ft_calculate_wall_line_height(t_game *game)
{
	double	wall_line_height;

	wall_line_height = (WINDOW_HEIGHT / game->img.perpendicular_dist);
	game->img.wall_line_start = WINDOW_HEIGHT / 2 - wall_line_height / 2;
	game->img.wall_line_end = WINDOW_HEIGHT / 2 + wall_line_height / 2;
}
