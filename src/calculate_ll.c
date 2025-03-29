/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:00:19 by livieira          #+#    #+#             */
/*   Updated: 2025/03/28 23:16:48 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calculate_line_height(t_game *game, t_render_info *info)
{
	info->draw_start = (int)floor(game->img.wall_line_start);
	info->draw_end = (int)floor(game->img.wall_line_end);
	info->line_height = info->draw_end - info->draw_start;
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

void	ft_calculate_tex_x(t_game *game, t_render_info *info, \
	double wall_x)
{
	info->tex_x = (int)((wall_x - floor(wall_x)) * (double)TEX_WIDTH);
	if ((game->img.hit_side == 0 && game->camera.ray_dir[0] > 0) || \
		(game->img.hit_side == 1 && game->camera.ray_dir[1] < 0))
		info->tex_x = TEX_WIDTH - info->tex_x - 1;
}
