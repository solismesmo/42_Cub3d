/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:41 by bruno             #+#    #+#             */
/*   Updated: 2025/01/28 00:46:50 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_init_player(t_game *game)
{
    game->player_info.vector_pos[0] = 5;
    game->player_info.vector_pos[1] = 5;
    game->player_info.vector_dir[0] = 0;
    game->player_info.vector_dir[1] = -1;
    game->player_info.x = 5;
    game->player_info.y = 5;
    game->camera.plane[0] = 0.66;
    game->camera.plane[1] = 0;
    ft_find_rays(game);
}

void ft_find_rays(t_game *game)
{
    int     pixels;
    float   multiplier; 
    float   camera_pixel[2];

    pixels = 0;
    multiplier = 0;
    game->camera.ray_dir[0] = 0;
    game->camera.ray_dir[1] = 0;
    while (pixels <= WINDOW_WIDTH)
    {
        multiplier = 2.0f * ((float)pixels / (float)WINDOW_WIDTH) -1.0f;
        camera_pixel[0] = game->camera.plane[0] * multiplier;
        camera_pixel[1] = game->camera.plane[1] * multiplier;
        game->camera.ray_dir[0] = game->player_info.vector_dir[0] + camera_pixel[0];
        game->camera.ray_dir[1] = game->player_info.vector_dir[1] + camera_pixel[1];

        printf("Multiplicador: %.2f\n", multiplier);
        printf("Camere Pixel: [%.2f, %.2f]\n", camera_pixel[0], camera_pixel[1]);
        printf("Ray Dir: [%.2f, %.2f]\n", game->camera.ray_dir[0], game->camera.ray_dir[1]);
        ft_dda(game);
        pixels++;
    }
}
void ft_dda(t_game *game)
{
    float mag_raydir;
    float delta_distx;
    float delta_disty;
    float dist_side_x;
    float dist_side_y;
    float step_x;
    float step_y;
    int hit;
    float dda_line_size_x;
    float dda_line_size_y;
    int wall_map_pos[2];

    delta_distx = 0;
    delta_disty = 0;
    step_x = 0;
    step_y = 0;
    hit = 0;
    dda_line_size_x = 0;
    dda_line_size_y = 0;
    
    mag_raydir = hypotf(game->camera.ray_dir[0], game->camera.ray_dir[1]);
    delta_distx = fabs(mag_raydir/game->camera.ray_dir[0]);
    delta_disty = fabs(mag_raydir/game->camera.ray_dir[1]);
    game->player_info.square_pos[0] = (int)game->player_info.vector_pos[0];
    game->player_info.square_pos[1] = (int)game->player_info.vector_pos[1];

    printf("Delta Dist X: %.2f\n", delta_distx);
    printf("Delta Dist Y: %.2f\n", delta_disty);
    printf("Map_square: [%d, %d]\n", game->player_info.square_pos[0], game->player_info.square_pos[1]);
    
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
    // while (hit == 0)
    // {
        
    // }
    
    
}