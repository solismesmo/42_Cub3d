/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:37:08 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 13:44:49 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_image(t_game *game, int pixels, mlx_image_t *image)
{
	double			wall_x;

	ft_calculate_line_height(game);
	if (game->info.line_height <= 0)
		return ;
	wall_x = ft_calculate_wall_x(game);
	ft_calculate_tex_x(game, wall_x);
	ft_initialize_texture_info(game);
	ft_render_texture_line(game, pixels, image);
}

void	ft_initialize_texture_info(t_game *game)
{
	game->info.step = 1.0 * TEX_HEIGHT / game->info.line_height;
	game->info.tex_pos = (game->info.draw_start - (WINDOW_HEIGHT / 2.0 - \
		game->info.line_height / 2.0)) * game->info.step;
	if (game->info.draw_start < 0)
	{
		game->info.tex_pos += (0 - game->info.draw_start) * game->info.step;
		game->info.draw_start = 0;
	}
}

void	ft_render_texture_line(t_game *game, int pixels, mlx_image_t *image)
{
	int	y;
	int	tex_y;
	int	color;

	y = game->info.draw_start;
	if (game->info.draw_end >= WINDOW_HEIGHT)
		game->info.draw_end = WINDOW_HEIGHT - 1;
	while (y < game->info.draw_end)
	{
		tex_y = (int)game->info.tex_pos & (TEX_HEIGHT - 1);
		game->info.tex_pos += game->info.step;
		color = get_texture_pixel(game, game->info.tex_x, tex_y);
		mlx_put_pixel(image, pixels, y, color);
		y++;
	}
}
