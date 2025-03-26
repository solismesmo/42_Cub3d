/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:41 by bruno             #+#    #+#             */
/*   Updated: 2025/03/26 18:04:49 by livieira         ###   ########.fr       */
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
void ft_check_path(char *path)
{
	if (!path || !(*path))
		return;
	while(*path != '\n')
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
		ft_error("Error: Trying to open texture path", game);
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
	if(!*image)
		ft_error("Error: Invalid texture path\n", game);
	mlx_delete_texture(my_texture);
}

void	ft_init_image(t_game *game)
{
	mlx_image_t*	img;
	int 			x;
	int 			y;

	y = 0;
	img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	memset(img->pixels, 255, img->width * img->height * BPP);
	mlx_image_to_window(game->mlx, img, 0, 0);
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
			mlx_put_pixel(img, x, y,  game->floor_color);
			x++;
		}
		y++;
	}
	game->img.image = img;
}

unsigned int	fix_color(unsigned int color)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	t = ((unsigned char *)&color)[0];
	r = ((unsigned char *)&color)[1];
	g = ((unsigned char *)&color)[2];
	b = ((unsigned char *)&color)[3];    
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

int	get_texture_pixel(t_game *game, int texX, int texY)
{
    mlx_image_t *tex;

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
    int index = texY * TEX_WIDTH + texX;
    int *pixels = (int *)tex->pixels;
    int color = pixels[index];
    return fix_color(color);
}

void	ft_init_player(t_game *game)
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
	int		pixels;
	double	multiplier; 
	double	camera_pixel[2];

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
