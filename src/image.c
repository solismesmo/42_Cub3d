/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:55:05 by bruno             #+#    #+#             */
/*   Updated: 2025/04/03 16:11:39 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_game(t_game *game)
{
	ft_init_player(game);
	ft_init_textures(game);
	ft_init_image(game);
	ft_find_rays(game);
}

void	ft_init_image(t_game *game)
{
	mlx_image_t		*img;
	int				x;
	int				y;

	x = 0;
	y = 0;
	img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	memset(img->pixels, 255, img->width * img->height * BPP);
	mlx_image_to_window(game->mlx, img, 0, 0);
	ft_ceiling_floor(game, img, x, y);
	game->img.image = img;
}

void	ft_ceiling_floor(t_game *game, mlx_image_t *img, int x, int y)
{
	while (y < (WINDOW_HEIGHT) / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < (WINDOW_HEIGHT))
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}
