/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moviment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:50:14 by bruno             #+#    #+#             */
/*   Updated: 2025/04/03 15:38:39 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotate_player(t_game *game, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player_info.vector_dir[0];
	old_planex = game->camera.plane[0];
	game->player_info.vector_dir[0] = game->player_info.vector_dir[0] \
	* cos(angle) - game->player_info.vector_dir[1] * sin(angle);
	game->player_info.vector_dir[1] = old_dirx * sin(angle) + \
		game->player_info.vector_dir[1] * cos(angle);
	game->camera.plane[0] = game->camera.plane[0] * cos(angle) - \
		game->camera.plane[1] * sin(angle);
	game->camera.plane[1] = old_planex * sin(angle) + \
		game->camera.plane[1] * cos(angle);
	ft_refresh_img(game);
}

void	ft_strafe_player(t_game *game, double move_speed)
{
	double	new_posx;
	double	new_posy;
	double	perp_x;
	double	perp_y;

	perp_x = -game->player_info.vector_dir[1];
	perp_y = game->player_info.vector_dir[0];
	new_posx = game->player_info.vector_pos[0] + perp_x * move_speed;
	new_posy = game->player_info.vector_pos[1] + perp_y * move_speed;
	if (game->map.matrix[(int)game->player_info.vector_pos[1]] \
	[(int)new_posx] != '1')
		game->player_info.vector_pos[0] = new_posx;
	if (game->map.matrix[(int)new_posy] \
	[(int)game->player_info.vector_pos[0]] != '1')
		game->player_info.vector_pos[1] = new_posy;
	ft_refresh_img(game);
}

void	ft_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_player(game, 0.2);
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_player(game, -0.2);
	if ((keydata.key == MLX_KEY_RIGHT) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_rotate_player(game, 0.03);
	if ((keydata.key == MLX_KEY_LEFT) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_rotate_player(game, -0.03);
	if ((keydata.key == MLX_KEY_D) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_strafe_player(game, 0.2);
	if ((keydata.key == MLX_KEY_A) && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_strafe_player(game, -0.2);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_finish("See you soon \n", game);
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

	new_posx = game->player_info.vector_pos[0] + \
		game->player_info.vector_dir[0] * move_speed;
	new_posy = game->player_info.vector_pos[1] + \
		game->player_info.vector_dir[1] * move_speed;
	if (game->map.matrix[(int)game->player_info.vector_pos[1]] \
	[(int)new_posx] != '1')
		game->player_info.vector_pos[0] = new_posx;
	if (game->map.matrix[(int)new_posy] \
	[(int)game->player_info.vector_pos[0]] != '1')
		game->player_info.vector_pos[1] = new_posy;
	ft_refresh_img(game);
}
