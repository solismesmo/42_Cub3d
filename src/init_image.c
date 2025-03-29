/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:38:22 by livieira          #+#    #+#             */
/*   Updated: 2025/03/28 22:45:37 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_textures(t_game *game)
{
	ft_check_path(game->img.path_north);
	ft_check_path(game->img.path_south);
	ft_check_path(game->img.path_west);
	ft_check_path(game->img.path_east);
	ft_check_texture_path(game->img.path_north, game);
	ft_check_texture_path(game->img.path_south, game);
	ft_check_texture_path(game->img.path_west, game);
	ft_check_texture_path(game->img.path_east, game);
	ft_place_png(game, &game->img.north, game->img.path_north);
	ft_place_png(game, &game->img.south, game->img.path_south);
	ft_place_png(game, &game->img.west, game->img.path_west);
	ft_place_png(game, &game->img.east, game->img.path_east);
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

void	ft_init_game(t_game *game)
{
	ft_init_player(game);
	ft_init_textures(game);
	ft_init_image(game);
	ft_find_rays(game);
}

void	ft_ceiling_floor(t_game *game, mlx_image_t *img, int x, int y)
{
	x = 0;
	while (y < (WINDOW_HEIGHT) / 2)
	{
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
