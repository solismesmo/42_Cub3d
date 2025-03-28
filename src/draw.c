/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:37:08 by bruno             #+#    #+#             */
/*   Updated: 2025/03/27 22:00:45 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_texture_info(t_game *game, t_render_info *info)
{
	info->step = 1.0 * TEX_HEIGHT / info->line_height;
	info->tex_pos = (info->draw_start - (WINDOW_HEIGHT / 2.0 - \
		info->line_height / 2.0)) * info->step;
	if (info->draw_start < 0)
	{
		info->tex_pos += (0 - info->draw_start) * info->step;
		info->draw_start = 0;
	}
}

static void	ft_render_texture_line(t_game *game, int pixels, \
	mlx_image_t *image, t_render_info *info)
{
	int	y;
	int	tex_y;
	int	color;

	y = info->draw_start;
	if (info->draw_end >= WINDOW_HEIGHT)
		info->draw_end = WINDOW_HEIGHT - 1;
	while (y < info->draw_end)
	{
		tex_y = (int)info->tex_pos & (TEX_HEIGHT - 1);
		info->tex_pos += info->step;
		color = get_texture_pixel(game, info->tex_x, tex_y);
		mlx_put_pixel(image, pixels, y, color);
		y++;
	}
}

void	ft_draw_image(t_game *game, int pixels, mlx_image_t *image)
{
	t_render_info	info;
	double			wall_x;

	ft_calculate_line_height(game, &info);
	if (info.line_height <= 0)
		return ;
	wall_x = ft_calculate_wall_x(game);
	ft_calculate_tex_x(game, &info, wall_x);
	ft_initialize_texture_info(game, &info);
	ft_render_texture_line(game, pixels, image, &info);
}
