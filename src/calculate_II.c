/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:00:19 by livieira          #+#    #+#             */
/*   Updated: 2025/04/01 08:13:38 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calculate_line_height(t_game *game)
{
	game->info.draw_start = (int)floor(game->img.wall_line_start);
	game->info.draw_end = (int)floor(game->img.wall_line_end);
	game->info.line_height = game->info.draw_end - game->info.draw_start;
}

double	ft_calculate_wall_x(t_game *game)
{
	if (game->img.hit_side == 0)
		return (game->player_info.vector_pos[1] + \
			game->img.perpendicular_dist * game->camera.ray_dir[1]);
	else
		return (game->player_info.vector_pos[0] + \
			game->img.perpendicular_dist * game->camera.ray_dir[0]);
}

void	ft_calculate_tex_x(t_game *game, double wall_x)
{
	game->info.tex_x = (int)((wall_x - floor(wall_x)) * (double)TEX_WIDTH);
	if ((game->img.hit_side == 0 && game->camera.ray_dir[0] > 0) || \
		(game->img.hit_side == 1 && game->camera.ray_dir[1] < 0))
		game->info.tex_x = TEX_WIDTH - game->info.tex_x - 1;
}
