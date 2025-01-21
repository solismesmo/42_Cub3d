/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:41 by bruno             #+#    #+#             */
/*   Updated: 2025/01/20 23:13:08 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_player(t_game *game)
{
    game->player_info.vector_pos[0] = 5;
    game->player_info.vector_pos[1] = 5;
    game->player_info.vector_dir[0] = -1;
    game->player_info.vector_dir[1] = 0;
    game->player_info.x = 5;
    game->player_info.y = 5;
    game->camera.plane[0] = 0,66;
    game->camera.plane[1] = 0;
}

void ft_find_rays(void)
{
    int pixels;
    int multiplicator; 
    
    pixels = 320;
    pixels = 0;
    multiplicator = 2 * (pixels / WINDOW_WIDTH) -1;
    printf("Multiplicator: %d\n", multiplicator);

    while (pixels < WINDOW_WIDTH)
    {
        multiplicator = 2 * (pixels / WINDOW_WIDTH) -1;
        printf("Multiplicator: %d\n", multiplicator);
        printf("Pixels: %d\n", pixels);
        pixels++;
    }
    
}

