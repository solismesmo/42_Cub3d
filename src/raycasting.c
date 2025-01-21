/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:41 by bruno             #+#    #+#             */
/*   Updated: 2025/01/21 20:05:30 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_init_player(t_game *game)
{
    game->player_info.vector_pos[0] = 5;
    game->player_info.vector_pos[1] = 5;
    game->player_info.vector_dir[0] = -1;
    game->player_info.vector_dir[1] = 0;
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
    float   camere_pixel[2];
    float   ray_dir[2];

    pixels = 0;
    multiplier = 0;
    while (pixels < WINDOW_WIDTH)
    {
        multiplier = 2.0f * ((float)pixels / (float)WINDOW_WIDTH) -1.0f;
        camere_pixel[0] = game->camera.plane[0] * multiplier;
        camere_pixel[1] = game->camera.plane[1] * multiplier;
        ray_dir[0] = game->player_info.vector_dir[0] + camere_pixel[0];
        ray_dir[1] = game->player_info.vector_dir[1] + camere_pixel[1];
        printf("Multiplicador: %.2f\n", multiplier);
        printf("Pixels: %d\n", pixels);
        printf("Camere Pixel: [%.2f, %.2f]\n", camere_pixel[0], camere_pixel[1]);
        printf("Ray Dir: [%.2f, %.2f]\n", ray_dir[0], ray_dir[1]);
        
        pixels++;
    }
    
}
