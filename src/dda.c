/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:37:04 by bruno             #+#    #+#             */
/*   Updated: 2025/03/26 18:03:56 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_dda(t_game *game)
{
	double	delta_distx;
	double	delta_disty;
	double	dist_side_x;
	double	dist_side_y;
	double	step_x;
	double	step_y;
	double	dda_line_size_x;
	double	dda_line_size_y;
	int		wall_map_pos[2];
	double	wall_line_height;

	wall_line_height = 0;
	delta_distx = 0;
	delta_disty = 0;
	step_x = 0;
	step_y = 0;
	game->img.hit = 0;
	dda_line_size_x = 0;
	dda_line_size_y = 0;
	game->img.hit_side = -1;
	game->img.perpendicular_dist = 0;

	if (game->camera.ray_dir[0] != 0)
		delta_distx = fabs(1 / game->camera.ray_dir[0]);
	else
		delta_distx = INFINITY;
	if (game->camera.ray_dir[1] != 0)
		delta_disty = fabs(1 / game->camera.ray_dir[1]);
	else
		delta_disty = INFINITY;
	game->player_info.square_pos[0] = (int)game->player_info.vector_pos[0];
	game->player_info.square_pos[1] = (int)game->player_info.vector_pos[1];
	if (game->camera.ray_dir[0] < 0)
	{
		dist_side_x = (game->player_info.vector_pos[0] - game->player_info.square_pos[0]) * delta_distx;
		step_x = -1;
	}
	else
	{
		dist_side_x = (game->player_info.square_pos[0] + 1.0 - game->player_info.vector_pos[0]) * delta_distx;
		step_x = 1;
	}
	if (game->camera.ray_dir[1] < 0)
	{
		dist_side_y = (game->player_info.vector_pos[1] - game->player_info.square_pos[1]) * delta_disty;
		step_y = -1;
	}
	else
	{
		dist_side_y = (game->player_info.square_pos[1] + 1.0 - game->player_info.vector_pos[1]) * delta_disty;
		step_y = 1;
	}
	dda_line_size_x = dist_side_x;
	dda_line_size_y = dist_side_y;
	wall_map_pos[0] = game->player_info.square_pos[0];
	wall_map_pos[1] = game->player_info.square_pos[1];
	while (game->img.hit == 0)
	{
		if (dda_line_size_x < dda_line_size_y)
		{
			dda_line_size_x += delta_distx;
			wall_map_pos[0] += step_x;
			game->img.hit_side = 0;
		}
		else
		{
			dda_line_size_y += delta_disty;
			wall_map_pos[1] += step_y;
			game->img.hit_side = 1;
		}
		if (game->map.matrix[wall_map_pos[1]][wall_map_pos[0]] == '1')
			game->img.hit = 1;
	}
	if (game->img.hit_side == 0)
		game->img.perpendicular_dist = fabs((wall_map_pos[0] - game->player_info.vector_pos[0] + ((1 - step_x) / 2)) / game->camera.ray_dir[0]);
	else
		game->img.perpendicular_dist = fabs((wall_map_pos[1] - game->player_info.vector_pos[1] + ((1 - step_y) / 2)) / game->camera.ray_dir[1]);
	wall_line_height = (WINDOW_HEIGHT / game->img.perpendicular_dist);
	game->img.wall_line_start = WINDOW_HEIGHT / 2 - wall_line_height / 2;
	game->img.wall_line_end = WINDOW_HEIGHT / 2 + wall_line_height / 2;
}
