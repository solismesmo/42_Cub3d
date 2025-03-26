/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:37:08 by bruno             #+#    #+#             */
/*   Updated: 2025/03/26 18:05:04 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_image(t_game *game, int pixels, mlx_image_t *image)
{
	double	wallline_start;
	double	wallline_end;
	int		draw_start;
	int		draw_end;
	int		lineHeight;

	wallline_start = game->img.wall_line_start;
	wallline_end = game->img.wall_line_end;
	draw_end = (int)floor(wallline_start);
	draw_end = (int)floor(wallline_end);
	lineHeight = draw_end - draw_start;
    if (lineHeight <= 0)
        return;
    double wallX;
    if (game->img.hit_side == 0)
        wallX = game->player_info.vector_pos[1] + game->img.perpendicular_dist * game->camera.ray_dir[1];
    else
        wallX = game->player_info.vector_pos[0] + game->img.perpendicular_dist * game->camera.ray_dir[0];
    wallX -= floor(wallX);
    int texX = (int)(wallX * (double)TEX_WIDTH);
    if (game->img.hit_side == 0 && game->camera.ray_dir[0] > 0)
        texX = TEX_WIDTH - texX - 1;
    if (game->img.hit_side == 1 && game->camera.ray_dir[1] < 0)
        texX = TEX_WIDTH - texX - 1;
    double step = 1.0 * TEX_HEIGHT / lineHeight;
    double texPos = (draw_start - (WINDOW_HEIGHT / 2.0 - lineHeight / 2.0)) * step;
    if (draw_start < 0)
    {
        texPos += (0 - draw_start) * step;
        draw_start = 0;
    }
    if (draw_end >= WINDOW_HEIGHT)
        draw_end = WINDOW_HEIGHT - 1;
    for (int y = draw_start; y < draw_end; y++)
    {
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        int color = get_texture_pixel(game, texX, texY);
        mlx_put_pixel(image, pixels, y, color);
    }
}
