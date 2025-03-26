/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moviment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:50:14 by bruno             #+#    #+#             */
/*   Updated: 2025/03/26 17:03:07 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotate_player(t_game *game, double angle)
{
	double old_dirx; 
	double old_planex;
	
	old_dirx = game->player_info.vector_dir[0];
	old_planex = game->camera.plane[0];
	game->player_info.vector_dir[0] = game->player_info.vector_dir[0] * cos(angle) - game->player_info.vector_dir[1] * sin(angle);
	game->player_info.vector_dir[1] = old_dirx * sin(angle) + game->player_info.vector_dir[1] * cos(angle);
	game->camera.plane[0] = game->camera.plane[0] * cos(angle) - game->camera.plane[1] * sin(angle);
	game->camera.plane[1] = old_planex * sin(angle) + game->camera.plane[1] * cos(angle);

	ft_refresh_img(game);
}

void	ft_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_player(game, 0.4);
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_player(game, -0.4);
	if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_rotate_player(game, 0.05);
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_rotate_player(game, -0.05);
	 if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	 {
	 	ft_finish("See you soon", game);
	 }
}

void	ft_refresh_img(t_game *game)
{
	mlx_ft_delete_image(game->mlx, game->img.image);
	ft_init_image(game);
	ft_find_rays(game);
}

void	ft_move_player(t_game *game, double move_speed)
{
    double	new_posx;
    double	new_posy;

    new_posx = game->player_info.vector_pos[0] + game->player_info.vector_dir[0] * move_speed;
    new_posy = game->player_info.vector_pos[1] + game->player_info.vector_dir[1] * move_speed;
    if (game->map.matrix[(int)game->player_info.vector_pos[1]][(int)new_posx] != '1')
        game->player_info.vector_pos[0] = new_posx;
    if (game->map.matrix[(int)new_posy][(int)game->player_info.vector_pos[0]] != '1')
        game->player_info.vector_pos[1] = new_posy;
    ft_refresh_img(game);
}
