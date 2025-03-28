/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:37:04 by bruno             #+#    #+#             */
/*   Updated: 2025/03/27 21:31:13 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_side_dist_and_step_x(t_game *game, \
	t_dda_params *params)
{
	game->player_info.square_pos[0] = (int)game->player_info.vector_pos[0];
	if (game->camera.ray_dir[0] < 0)
	{
		params->dist_side_x = (game->player_info.vector_pos[0] - \
			game->player_info.square_pos[0]) * params->delta_distx;
		params->step_x = -1;
	}
	else
	{
		params->dist_side_x = (game->player_info.square_pos[0] + 1.0 - \
			game->player_info.vector_pos[0]) * params->delta_distx;
		params->step_x = 1;
	}
}

static void	ft_initialize_side_dist_and_step_y(t_game *game, \
	t_dda_params *params)
{
	game->player_info.square_pos[1] = (int)game->player_info.vector_pos[1];
	if (game->camera.ray_dir[1] < 0)
	{
		params->dist_side_y = (game->player_info.vector_pos[1] - \
			game->player_info.square_pos[1]) * params->delta_disty;
		params->step_y = -1;
	}
	else
	{
		params->dist_side_y = (game->player_info.square_pos[1] + 1.0 - \
			game->player_info.vector_pos[1]) * params->delta_disty;
		params->step_y = 1;
	}
}

static void	ft_update_dda_line_size(t_dda_params *params)
{
	params->dda_line_size_x = params->dist_side_x;
	params->dda_line_size_y = params->dist_side_y;
}

static void	ft_perform_dda_loop(t_game *game, t_dda_params *params)
{
	while (game->img.hit == 0)
	{
		if (params->dda_line_size_x < params->dda_line_size_y)
		{
			params->dda_line_size_x += params->delta_distx;
			params->wall_map_pos[0] += params->step_x;
			game->img.hit_side = 0;
		}
		else
		{
			params->dda_line_size_y += params->delta_disty;
			params->wall_map_pos[1] += params->step_y;
			game->img.hit_side = 1;
		}
		if (game->map.matrix[params->wall_map_pos[1]][params->wall_map_pos[0]] \
			== '1')
			game->img.hit = 1;
	}
}

void	ft_dda(t_game *game)
{
	t_dda_params	params;

	params.wall_map_pos[0] = game->player_info.square_pos[0];
	params.wall_map_pos[1] = game->player_info.square_pos[1];
	game->img.hit = 0;
	game->img.hit_side = -1;
	game->img.perpendicular_dist = 0;
	ft_calculate_delta_dist(game, &params);
	ft_initialize_side_dist_and_step_x(game, &params);
	ft_initialize_side_dist_and_step_y(game, &params);
	ft_update_dda_line_size(&params);
	ft_perform_dda_loop(game, &params);
	ft_calculate_perpendicular_dist(game, &params);
	ft_calculate_wall_line_height(game);
}
