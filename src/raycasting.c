/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:41 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 11:28:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int fix_color(unsigned int color)
{
    unsigned char t = ((unsigned char *)&color)[0];
    unsigned char r = ((unsigned char *)&color)[1];
    unsigned char g = ((unsigned char *)&color)[2];
    unsigned char b = ((unsigned char *)&color)[3];
    
    return ((t << 24) | (r << 16) | (g << 8) | b);
}

int get_texture_pixel(t_game *game, int texX, int texY)
{
	mlx_image_t	*tex;
	int			index;
	int			*pixels;
	int			color;

    if (game->img.hit_side == 0)
    {
        if (game->camera.ray_dir[0] > 0)
            tex = game->img.east;
        else
            tex = game->img.west;
    }
    else
    {
        if (game->camera.ray_dir[1] > 0)
            tex = game->img.south;
        else
            tex = game->img.north;
    }
    if (!tex || !tex->pixels)
        return 0;
    index = texY * TEX_WIDTH + texX;
    pixels = (int *)tex->pixels;
    color = pixels[index];
    return fix_color(color);
}

void    ft_init_player(t_game *game)
{
	game->player_info.vector_pos[0] = game->map.p_col + 0.5;
	game->player_info.vector_pos[1] = game->map.p_row + 0.5;
	game->player_info.vector_dir[0] = -1;
	game->player_info.vector_dir[1] = 0;	
	game->player_info.x = game->map.p_col;
	game->player_info.y = game->map.p_row;
	game->camera.plane[0] = 0;
	game->camera.plane[1] = -0.66;
}

void ft_find_rays(t_game *game)
{
	int     pixels;
	double  multiplier; 
	double  camera_pixel[2];

	pixels = 0;
	multiplier = 0;
	game->camera.ray_dir[0] = 0;
	game->camera.ray_dir[1] = 0;
	while (pixels <= WINDOW_WIDTH)
	{
		multiplier = 2.0 * ((double)pixels / (double)WINDOW_WIDTH) - 1.0;
		camera_pixel[0] = game->camera.plane[0] * multiplier;
		camera_pixel[1] = game->camera.plane[1] * multiplier;
		game->camera.ray_dir[0] = game->player_info.vector_dir[0] + camera_pixel[0];
		game->camera.ray_dir[1] = game->player_info.vector_dir[1] + camera_pixel[1];
		ft_dda(game);
		ft_draw_image(game, pixels, game->img.image);
		pixels++;
	}
}