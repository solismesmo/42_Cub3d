/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:37:08 by bruno             #+#    #+#             */
/*   Updated: 2025/03/26 19:05:58 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_image(t_game *game, int pixels, mlx_image_t *image)
{
	double	wallline_start;
	double	wallline_end;
	int		draw_start;
	int		draw_end;
	int		line_height;

	wallline_start = game->img.wall_line_start;
	wallline_end = game->img.wall_line_end;
	draw_end = (int)floor(wallline_start);
	draw_end = (int)floor(wallline_end);
	line_height = draw_end - draw_start;
    if (line_height <= 0)
        return;
    double wall_x;
    if (game->img.hit_side == 0)
        wall_x = game->player_info.vector_pos[1] + \
        game->img.perpendicular_dist * game->camera.ray_dir[1];
    else
        wall_x = game->player_info.vector_pos[0] + \
        game->img.perpendicular_dist * game->camera.ray_dir[0];
    wall_x -= floor(wall_x);
    int tex_x = (int)(wall_x * (double)TEX_WIDTH);
    if (game->img.hit_side == 0 && game->camera.ray_dir[0] > 0)
        tex_x = TEX_WIDTH - tex_x - 1;
    if (game->img.hit_side == 1 && game->camera.ray_dir[1] < 0)
        tex_x = TEX_WIDTH - tex_x - 1;
    double step = 1.0 * TEX_HEIGHT / line_height;
    double tex_pos = (draw_start - (WINDOW_HEIGHT / 2.0 - line_height / 2.0)) \
    * step;
    if (draw_start < 0)
    {
        tex_pos += (0 - draw_start) * step;
        draw_start = 0;
    }
    if (draw_end >= WINDOW_HEIGHT)
        draw_end = WINDOW_HEIGHT - 1;
    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
        tex_pos += step;
        int color = get_texture_pixel(game, tex_x, tex_y);
        mlx_put_pixel(image, pixels, y, color);
    }
}
