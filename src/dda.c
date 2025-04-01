/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:37:04 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 13:47:18 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_dda(t_game *game)
{
	game->params.wall_map_pos[0] = game->player_info.square_pos[0];
	game->params.wall_map_pos[1] = game->player_info.square_pos[1];
	game->img.hit = 0;
	game->img.hit_side = -1;
	game->img.perpendicular_dist = 0;
	ft_calculate_delta_dist(game);
	ft_initialize_side_dist_and_step_x(game);
	ft_initialize_side_dist_and_step_y(game);
	ft_update_dda_line_size(game);
	ft_perform_dda_loop(game);
	ft_calculate_perpendicular_dist(game);
	ft_calculate_wall_line_height(game);
}

void	ft_initialize_side_dist_and_step_x(t_game *game)
{
	game->player_info.square_pos[0] = (int)game->player_info.vector_pos[0];
	if (game->camera.ray_dir[0] < 0)
	{
		game->params.dist_side_x = (game->player_info.vector_pos[0] - \
		game->player_info.square_pos[0]) * game->params.delta_distx;
		game->params.step_x = -1;
	}
	else
	{
		game->params.dist_side_x = (game->player_info.square_pos[0] + 1.0 - \
		game->player_info.vector_pos[0]) * game->params.delta_distx;
		game->params.step_x = 1;
	}
}

void	ft_initialize_side_dist_and_step_y(t_game *game)
{
	game->player_info.square_pos[1] = (int)game->player_info.vector_pos[1];
	if (game->camera.ray_dir[1] < 0)
	{
		game->params.dist_side_y = (game->player_info.vector_pos[1] - \
			game->player_info.square_pos[1]) * game->params.delta_disty;
		game->params.step_y = -1;
	}
	else
	{
		game->params.dist_side_y = (game->player_info.square_pos[1] + 1.0 - \
		game->player_info.vector_pos[1]) * game->params.delta_disty;
		game->params.step_y = 1;
	}
}

void	ft_update_dda_line_size(t_game *game)
{
	game->params.dda_line_size_x = game->params.dist_side_x;
	game->params.dda_line_size_y = game->params.dist_side_y;
}

void	ft_perform_dda_loop(t_game *game)
{
	while (game->img.hit == 0)
	{
		if (game->params.dda_line_size_x < game->params.dda_line_size_y)
		{
			game->params.dda_line_size_x += game->params.delta_distx;
			game->params.wall_map_pos[0] += game->params.step_x;
			game->img.hit_side = 0;
		}
		else
		{
			game->params.dda_line_size_y += game->params.delta_disty;
			game->params.wall_map_pos[1] += game->params.step_y;
			game->img.hit_side = 1;
		}
		if (game->map.matrix[game->params.wall_map_pos[1]][game->params.wall_map_pos[0]] == '1')
			game->img.hit = 1;
	}
}
