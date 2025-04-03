/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:49:17 by bruno             #+#    #+#             */
/*   Updated: 2025/04/01 23:19:40 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_path(char *path)
{
	if (!path || !(*path))
		return ;
	while (*path != '\n')
	{
		path++;
	}
	*path = '\0';
}

int	ft_check_texture_path(const char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_error("Error: Trying to open texture path\n", game);
		return (0);
	}
	close(fd);
	return (1);
}

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

void	ft_place_png(t_game *game, mlx_image_t **image, char *path)
{
	mlx_texture_t	*my_texture;

	my_texture = mlx_load_png(path);
	*image = mlx_texture_to_image(game->mlx, my_texture);
	if (!*image)
		ft_error("Error: Invalid texture path\n", game);
	mlx_delete_texture(my_texture);
}
